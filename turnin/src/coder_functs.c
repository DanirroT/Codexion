/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/17 23:31:40 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_compile(t_coder *self)
{
	if (check_burnout(self->room))
		return ;
	take_dongles(self);
	if (check_burnout(self->room))
	{
		free_dongles(self);
		return ;
	}
	pthread_mutex_lock(&self->compiling_m);
	self->last_ct = print_event(self->room, self->id, "is compiling");
	self->compilations_complete += 1;
	pthread_mutex_unlock(&self->compiling_m);
	safe_msleep(self->room->inputs->time_to_compile, self->room);
	free_dongles(self);
}

static void	do_compile_loop(t_coder *self)
{
	if (check_burnout(self->room))
		return ;
	print_event(self->room, self->id, "is debugging");
	safe_msleep(self->room->inputs->time_to_debug, self->room);
	if (check_burnout(self->room))
		return ;
	print_event(self->room, self->id, "is refactoring");
	safe_msleep(self->room->inputs->time_to_refactor, self->room);
	do_compile(self);
}

static int	wait_for_burnout(t_programming_room *room)
{
	unsigned long long	timeout;
	int					i;
	int					id;
	int					out;

	out = 1;
	id = -1;
	while (out)
	{
		msleep(4);
		timeout = get_time_past(room->start_time);
		i = -1;
		out = 0;
		while (++i < room->inputs->number_of_coders && id == -1)
		{
			pthread_mutex_lock(&room->coders[i].compiling_m);
			if (room->coders[i].compilations_complete
				== room->inputs->number_of_compiles_required)
			{
				pthread_mutex_unlock(&room->coders[i].compiling_m);
				continue ;
			}
			if (room->coders[i].last_ct
				+ (long long)room->inputs->time_to_burnout
				<= timeout)
				id = room->coders[i].id;
			out = 1;
			pthread_mutex_unlock(&room->coders[i].compiling_m);
		}
	}
	return (id);
}

void	*coder_burnout(void *input_raw)
{
	t_programming_room	*room;
	int					id;

	room = (t_programming_room *) input_raw;
	safe_mod_val_int(&room->b_ready, DONE, &room->ready_m);
	safe_cond_timedwait(&room->start_sim_c, &room->start_sim_m,
		power(room->inputs->number_of_coders, 3) + 200, room);
	id = wait_for_burnout(room);
	if (id == -1)
		return (NULL);
	safe_mod_val_int(&room->burnout_state, DONE, &room->burnout_m);
	print_event(room, id, "burned out");
	return (NULL);
}

void	*coder_funct(void *input_raw)
{
	t_coder	*self;

	self = (t_coder *)input_raw;
	safe_mod_val_int(&self->c_ready, DONE, &self->room->ready_m);
	safe_cond_timedwait(&self->room->start_sim_c, &self->room->start_sim_m,
		power(self->room->inputs->number_of_coders, 3) + 200, self->room);
	// safe_cond_wait(&self->room->start_sim_c, &self->room->start_sim_m,
	// 	self->room);
	fprintf(stderr, "C%i Stat!\n", self->id);
	if (!(self->id % 2))
		safe_msleep(self->room->inputs->time_to_compile - 20, self->room);
	do_compile(self);
	pthread_mutex_lock(&self->compiling_m);
	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& !check_burnout(self->room))
	{
		pthread_mutex_unlock(&self->compiling_m);
		do_compile_loop(self);
		pthread_mutex_lock(&self->compiling_m);
	}
	pthread_mutex_unlock(&self->compiling_m);
	return (NULL);
}
