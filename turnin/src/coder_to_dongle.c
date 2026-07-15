/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_to_dongle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 19:03:01 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/06/26 18:51:40 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	request_dongles(t_coder *self, t_dongle **first, t_dongle **second)
{
	if (check_burnout(self->room))
		return ;
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
		return ;
	add_d_queue(*first, self);
	add_d_queue(*second, self);
}

static void	wait_for_ready(t_coder *self, t_dongle *first, t_dongle *second)
{
	struct timespec	offset;

	offset = get_timespec_offset(self->room->inputs->time_to_burnout);
	pthread_mutex_lock(&first->state_m);
	if (!check_burnout(self->room) && first->state == HELD)
		pthread_cond_timedwait(&first->ready, &first->state_m, &offset);
	pthread_mutex_unlock(&first->state_m);
	pthread_mutex_lock(&second->state_m);
	if (!check_burnout(self->room) && second->state == HELD)
		pthread_cond_timedwait(&second->ready, &second->state_m, &offset);
	pthread_mutex_unlock(&second->state_m);
}

void	take_dongles(t_coder *self)
{
	t_dongle		*first;
	t_dongle		*second;

	request_dongles(self, &first, &second);
	while (!check_burnout(self->room))
	{
		pthread_mutex_lock(&first->state_m);
		pthread_mutex_lock(&second->state_m);
		if (first->state == FREE && second->state == FREE)
		{
			if (self == second->queue->content
				&& self == first->queue->content)
			{
				remove_from_queue(first);
				remove_from_queue(second);
				pthread_mutex_unlock(&second->state_m);
				pthread_mutex_unlock(&first->state_m);
				return ;
			}
		}
		pthread_mutex_unlock(&second->state_m);
		pthread_mutex_unlock(&first->state_m);
		wait_for_ready(self, first, second);
	}
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
	safe_broadcast(&first->free, &first->state_m);
	safe_broadcast(&second->free, &second->state_m);
}
