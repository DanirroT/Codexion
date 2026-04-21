/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_functs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 15:40:09 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/21 19:52:54 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	take_dongle(t_dongle *dongle, int id, struct timeval start)
{
	int	out;

	while (1)
	{
		if (!dongle->state)
		{
			out = pthread_mutex_lock(&dongle->mutex);
			dongle->state = 1;
			fprintf(stdout, "%lli %i has taken a dongle %i\n",
				get_time_past(start), id, dongle->id);
			fflush(stdout);
			return (out);
		}
	}
}

void	take_dongles(t_coder *self)
{
	if (self->id % 2)
	{
		take_dongle(self->dongle_l, self->id, self->room->start_time);
		take_dongle(self->dongle_r, self->id, self->room->start_time);
	}
	else
	{
		take_dongle(self->dongle_r, self->id, self->room->start_time);
		take_dongle(self->dongle_l, self->id, self->room->start_time);
	}
}

void	*dongle_cooldown(void *input_raw)
{
	t_dongle	*dongle;

	dongle = (t_dongle *) input_raw;
	fprintf(stdout, "\tDongle %i let go!\n", dongle->id);
	fflush(stdout);
	msleep(dongle->dongle_cooldown);
	dongle->state = 0;
	pthread_mutex_unlock(&dongle->mutex);
	pthread_cond_broadcast(&dongle->cond);
	fprintf(stdout, "\tDongle %i Free!\n", dongle->id);
	fflush(stdout);
	return (NULL);
}

void	free_dongles(t_coder *self)
{
	pthread_t	dongle_l;
	pthread_t	dongle_r;

	if (!self->room->burnout_state)
	{
		pthread_mutex_unlock(&self->dongle_l->mutex);
		pthread_mutex_unlock(&self->dongle_r->mutex);
		return ;
	}
	pthread_create(&dongle_l, NULL, dongle_cooldown, self->dongle_l);
	pthread_create(&dongle_r, NULL, dongle_cooldown, self->dongle_r);
}
