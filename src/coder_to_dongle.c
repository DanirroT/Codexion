/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_to_dongle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 22:31:12 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/17 17:15:04 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	request_dongles(t_coder *self, t_dongle **first, t_dongle **second)
{
	if (check_burnout(self->room) || self->dongle_l == self->dongle_r)
		return (0);
	if (self->id % 2)
	{
		*first = self->dongle_l;
		*second = self->dongle_r;
	}
	else
	{
		*first = self->dongle_r;
		*second = self->dongle_l;
	}
	if (check_burnout(self->room))
		return (1);
	fprintf(stderr, "C%i requests 1st D%i\n", self->id, (*first)->id);
	add_d_queue(*first, self);
	fprintf(stderr, "C%i requests 2nd D%i\n", self->id, (*second)->id);
	add_d_queue(*second, self);
	fprintf(stderr, "\tC%i request done\n", self->id);
	return (0);
}

static void	wait_for_ready(t_coder *self, t_dongle *first, t_dongle *second)
{
	struct timespec	offset;

	fprintf(stderr, "C%i waiting for 1st D%i-ready %p (%p)\n",
		self->id, first->id, &first->ready, &first->state_m);
	offset = get_timespec_offset(self->room->inputs->time_to_burnout);
	pthread_mutex_lock(&first->state_m);
	if (!check_burnout(self->room) && first->state == HELD)
		pthread_cond_timedwait(&first->ready, &first->state_m, &offset);
	pthread_mutex_unlock(&first->state_m);
	fprintf(stderr, "C%i waiting for 2nd D%i-ready %p (%p)\n",
		self->id, second->id, &second->ready, &second->state_m);
	pthread_mutex_lock(&second->state_m);
	if (!check_burnout(self->room) && second->state == HELD)
		pthread_cond_timedwait(&second->ready, &second->state_m, &offset);
	pthread_mutex_unlock(&second->state_m);
	fprintf(stderr, "C%i Both Ready %i & %i\n",
		self->id, first->id, second->id);
}

void	take_dongles(t_coder *self)
{
	t_dongle		*first;
	t_dongle		*second;

	fprintf(stderr, "C%i in take_dongles\n", self->id);
	if (request_dongles(self, &first, &second))
		return ;
	while (!check_burnout(self->room) && first != second)
	{
		pthread_mutex_lock(&first->state_m);
		pthread_mutex_lock(&second->state_m);
		fprintf(stderr, "C%i Checking D%i & D%i\n",
			self->id, first->id, second->id);
		if (first->state == FREE && second->state == FREE)
		{
			fprintf(stderr, "C%i: D%i & D%i FREE\n",
				self->id, first->id, second->id);
			print_queue(first->queue, first->id, "In");
			print_queue(second->queue, second->id, "In");
			if (self == second->queue->content
				&& self == first->queue->content)
			{
				fprintf(stderr, "C%i taking Dongles\n", self->id);
				remove_from_queue(first, self->id);
				remove_from_queue(second, self->id);
				pthread_mutex_unlock(&second->state_m);
				pthread_mutex_unlock(&first->state_m);
				fprintf(stderr, "C%i Dongles taken\n", self->id);
				return ;
			}
		}
		pthread_mutex_unlock(&second->state_m);
		pthread_mutex_unlock(&first->state_m);
		wait_for_ready(self, first, second);
	}
	fprintf(stderr, "C%i out take_dongles, state: %i\n",
		self->id, self->room->burnout_state);
}

void	free_dongles(t_coder *self)
{
	t_dongle	*first;
	t_dongle	*second;

	if (self->id % 2)
	{
		first = self->dongle_l;
		second = self->dongle_r;
	}
	else
	{
		first = self->dongle_r;
		second = self->dongle_l;
	}
	fprintf(stderr, "\tC%i FREEs D%i & D%i\n", self->id, first->id, second->id);
	safe_broadcast(&first->free, &first->state_m);
	safe_broadcast(&second->free, &second->state_m);
}
