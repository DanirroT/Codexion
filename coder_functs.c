/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/21 22:30:23 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	do_compile(t_coder *self)
{
	long long	start_time;

	if (!self->room->burnout_state)
		return ;
	take_dongles(self);
	if (!self->room->burnout_state)
	{
		free_dongles(self);
		return ;
	}
	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%llu %i is compiling %i\n", start_time,
		self->id, self->compilations_complete);
	fflush(stdout);
	// self->last_compile_time = start_time;
	self->compilations_complete += 1;
	msleep(self->room->inputs->time_to_compile);
	free_dongles(self);
}

void	do_debug(t_coder *self)
{
	long long	start_time;

	if (!self->room->burnout_state)
		return ;
	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli Coder %i is debugging\n", start_time, self->id);
	fflush(stdout);
	msleep(self->room->inputs->time_to_debug);
}

void	do_refactor(t_coder *self)
{
	long long	start_time;

	if (!self->room->burnout_state)
		return ;
	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli Coder %i is refactoring\n", start_time, self->id);
	fflush(stdout);
	msleep(self->room->inputs->time_to_refactor);
}


void	*coder_burnout(void *input_raw)
{
	t_coder	*self;
	int		res;

	self = (t_coder *) input_raw;
	while (1)
	{
		if (self->compilations_complete
			>= self->room->inputs->number_of_compiles_required
			|| !self->room->burnout_state)
			return (NULL);
		res = cond_timedwait(&self->compiling_c, &self->compiling_m,
			&self->room->burnout_state, self->room->inputs->time_to_burnout);
		fprintf(stderr, "coder_burnout res %i\n", res);
		fflush(stderr);
		if (res == 0)
		{
			fprintf(stdout, "%llu %i Burned Out!\n", get_time_past(self->room->start_time), self->id);
			fflush(stdout);
			pthread_mutex_lock(&self->room->burnout_m);
			self->room->burnout_state = 0;
			pthread_mutex_unlock(&self->room->burnout_m);
			ft_out(self->room, NULL, 1, "A coder has burned out! Simulation ending.");
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
	t_coder	*self;

	self = (t_coder *) input_raw;
	fprintf(stderr, "Hello from coder thread %i!\n", self->id);
	cond_wait(&self->room->start_sim_c, &self->room->start_sim_m,
		&self->room->burnout_state);
	pthread_create(&self->burnout_thread, NULL, coder_burnout, self);
	if (!(self->id % 2))
		msleep(5);
	do_compile(self);
	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& self->room->burnout_state)
	{
		do_refactor(self);
		do_compile(self);
		free_dongles(self);
	}
	fprintf(stderr, "Coder %i is Finished!\n", self->id);
	return (NULL);
}
