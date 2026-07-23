/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_n_burnout_functs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:40:09 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/22 14:18:20 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	dongle_main_loop(t_dongle *self)
{
	struct timespec	offset;
	int				req;

	req = 0;
	while (!check_burnout(self->room) && !req)
	{
		pthread_mutex_lock(&self->state_m);
		self->state = FREE;
		pthread_cond_broadcast(&self->ready);
		if (!check_burnout(self->room))
		{
			offset = get_timespec_offset(self->room->inputs->time_to_burnout
					+ self->room->inputs->time_to_compile);
			req = pthread_cond_timedwait(&self->free, &self->state_m, &offset);
		}
		pthread_mutex_unlock(&self->state_m);
		if (req)
			return ;
		safe_msleep(self->room->inputs->dongle_cooldown, self->room);
	}
}

void	*dongle_funct(void *input_raw)
{
	t_dongle	*self;

	self = (t_dongle *)input_raw;
	safe_mod_val_int(&self->d_ready, DONE, &self->room->ready_m);
	safe_cond_timedwait(&self->room->start_sim_c, &self->room->start_sim_m,
		power(self->room->inputs->number_of_coders, 3) + 200, self->room);
	dongle_main_loop(self);
	return (NULL);
}

static int	check_all_coders(t_programming_room *room,
	unsigned long long timeout, int *out)
{
	int	i;

	i = -1;
	*out = 0;
	while (++i < room->inputs->number_of_coders)
	{
		pthread_mutex_lock(&room->coders[i].compiling_m);
		if (room->coders[i].compilations_complete
			!= room->inputs->number_of_compiles_required)
		{
			*out = 1;
			if (room->coders[i].last_ct
				+ (unsigned long long)room->inputs->time_to_burnout
				<= timeout)
			{
				pthread_mutex_unlock(&room->coders[i].compiling_m);
				return (room->coders[i].id);
			}
		}
		pthread_mutex_unlock(&room->coders[i].compiling_m);
	}
	return (-1);
}

static int	wait_for_burnout(t_programming_room *room)
{
	unsigned long long	timeout;
	int					out_id;
	int					out;

	out = 1;
	while (out)
	{
		msleep(4);
		timeout = get_time_past(room->start_time);
		out_id = check_all_coders(room, timeout, &out);
		if (out_id != -1)
			return (out_id);
	}
	return (-1);
}

void	*coder_burnout(void *input_raw)
{
	t_programming_room	*room;
	unsigned long long	time_past;
	int					id;

	room = (t_programming_room *) input_raw;
	safe_mod_val_int(&room->b_ready, DONE, &room->ready_m);
	safe_cond_timedwait(&room->start_sim_c, &room->start_sim_m,
		power(room->inputs->number_of_coders, 3) + 200, room);
	msleep(2);
	id = wait_for_burnout(room);
	if (id == -1)
		return (NULL);
	pthread_mutex_lock(&room->print_m);
	pthread_mutex_lock(&room->burnout_m);
	time_past = get_time_past(room->start_time);
	printf("%llu %i %s\n", time_past, id, "burned out");
	room->burnout_state = DONE;
	pthread_mutex_unlock(&room->burnout_m);
	msleep(room->inputs->time_to_burnout / 2);
	pthread_mutex_unlock(&room->print_m);
	return (NULL);
}
