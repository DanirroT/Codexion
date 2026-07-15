/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_functs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:40:09 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/15 23:32:46 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	dongle_main_loop(t_dongle *self)
{
	struct timespec	offset;

	fprintf(stderr, "start dongle_main_loop D%i\n", self->id);
	fflush(stderr);
	while (!check_burnout(self->room))
	{
		pthread_mutex_lock(&self->state_m);
		self->state = FREE;
		fprintf(stderr, "D%i: Broadcast Ready %p (%p)\n",
			self->id, &self->ready, &self->state_m);
		pthread_cond_broadcast(&self->ready);
		if (!check_burnout(self->room))
		{
			offset = get_timespec_offset(self->room->inputs->time_to_burnout
										 + self->room->inputs->time_to_compile);
			pthread_cond_timedwait(&self->free, &self->state_m, &offset);
		}
		pthread_mutex_unlock(&self->state_m);
		fprintf(stderr, "D%i: Received FREE Broadcast\n", self->id);
		safe_msleep(self->room->inputs->dongle_cooldown, self->room);
	}
	fprintf(stderr, "end dongle_main_loop D%i\n", self->id);
	fflush(stderr);
}

void	*dongle_funct(void *input_raw)
{
	t_dongle	*self;

	self = (t_dongle *)input_raw;
	fprintf(stderr, "Hello from D%i\n", self->id);
	safe_mod_val_int(&self->d_ready, DONE, &self->room->ready_m);
	safe_cond_timedwait(&self->room->start_sim_c, &self->room->start_sim_m,
		power(self->room->inputs->number_of_coders, 3) + 200, self->room);
	fprintf(stderr, "Hello from D%i\n", self->id);
	dongle_main_loop(self);
	fprintf(stderr, "Goodbye from D%i\n", self->id);
	return (NULL);
}
