/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/21 22:21:39 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	do_compile(t_coder *self)
{
	long long	start_time;

	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli Coder %i is compiling %i\n", start_time, self->id, self->compilations_complete);
	fflush(stdout);
	self->last_compile_time = start_time;
	self->compilations_complete += 1;
	msleep(self->room->inputs->time_to_compile);

}

void	do_debug(t_coder *self)
{
	long long	start_time;

	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli Coder %i is debugging\n", start_time, self->id);
	fflush(stdout);
	msleep(self->room->inputs->time_to_debug);

}

void	do_refactor(t_coder *self)
{
	long long	start_time;

	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli Coder %i is refactoring\n", start_time, self->id);
	fflush(stdout);

	msleep(self->room->inputs->time_to_refactor);
}

int	take_dongle(t_dongle *dongle, int id, struct timeval start)
{
	int out;

	while (1)
	{
		if (!dongle->state)
		{
			out = pthread_mutex_lock(&dongle->mutex);
			dongle->state = 1;
			fprintf(stdout, "%lli Coder %i has taken a dongle %i\n", get_time_past(start), id, dongle->id);
			fflush(stdout);
			return (out);
		}
	}
}

void	*dongle_cooldown(void *input_raw)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)input_raw;

	msleep(dongle->dongle_cooldown);

	// cond_timedwait(&dongle->state,
	// 	&dongle->mutex, 50);
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

	fprintf(stdout, "\tCoder %i let go of dongles %i and %i\n", self->id, self->dongle_l->id, self->dongle_r->id);
	fflush(stdout);
	pthread_create(&dongle_l, NULL, dongle_cooldown, self->dongle_l);
	pthread_create(&dongle_r, NULL, dongle_cooldown, self->dongle_r);
}

void	*coder_funct(void *input_raw)
{
	t_coder				*self;

	self = (t_coder *)input_raw;

	fprintf(stderr, "Hello from coder thread %i!\n", self->id);

	cond_wait(&self->room->start_sim_c, &self->room->start_sim_m, &self->room->burnout_state);

	fprintf(stderr, "\tSTART %i!\n", self->id);

	if (!(self->id % 2))
		msleep(5);

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

	do_compile(self);
	free_dongles(self);
	while (self->compilations_complete < self->room->inputs->number_of_compiles_required)
	{
		do_debug(self);
		do_refactor(self);
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
		do_compile(self);
		free_dongles(self);
	}
	fprintf(stderr, "Coder %i is Finished!\n", self->id);

	return (NULL);
}
