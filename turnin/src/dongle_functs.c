/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_functs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:40:09 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/14 18:49:57 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	dongle_main_loop(t_dongle *self)
{
	int				req;
	struct timespec	offset;

	while (!check_burnout(self->room))
	{
		pthread_mutex_lock(&self->state_m);
		self->state = FREE;
		pthread_cond_broadcast(&self->ready);
		if (!check_burnout(self->room))
		{
			offset = get_timespec_offset(self->room->inputs->time_to_burnout
										 + self->room->inputs->time_to_compile);
			pthread_cond_timedwait(&self->free, &self->state_m, &offset);
		}
		pthread_mutex_unlock(&self->state_m);
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
	fprintf(stderr, "Hello from D%i\n", self->id);
	dongle_main_loop(self);
	fprintf(stderr, "Goodbye from D%i\n", self->id);
	return (NULL);
}
