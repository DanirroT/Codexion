/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/23 19:53:22 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	do_compile(t_coder *self)
{
	long long	start_time;

	if (!self->room->burnout_state)
		return ;
	take_dongles(self, self->room->print_m);
	if (!self->room->burnout_state)
	{
		free_dongles(self);
		return ;
	}
	start_time = get_time_past(self->room->start_time);
	pthread_mutex_lock(&self->room->print_m);
	fprintf(stdout, "%llu %i is compiling %i\n", start_time,
		self->id, self->compilations_complete);
	fflush(stdout);
	pthread_mutex_unlock(&self->room->print_m);
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
	pthread_mutex_lock(&self->room->print_m);
	fprintf(stdout, "%lli Coder %i is debugging\n", start_time, self->id);
	fflush(stdout);
	pthread_mutex_unlock(&self->room->print_m);
	msleep(self->room->inputs->time_to_debug);
}

void	do_refactor(t_coder *self)
{
	long long	start_time;

	if (!self->room->burnout_state)
		return ;
	start_time = get_time_past(self->room->start_time);
	pthread_mutex_lock(&self->room->print_m);
	fprintf(stdout, "%lli Coder %i is refactoring\n", start_time, self->id);
	fflush(stdout);
	pthread_mutex_unlock(&self->room->print_m);
	msleep(self->room->inputs->time_to_refactor);
}


void	*coder_burnout(void *input_raw)
{
	t_coder	*self;
	int		res;

	self = (t_coder *) input_raw;

	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& !self->room->burnout_state)
	{
		res = cond_timedwait(&self->compiling_c, &self->compiling_m,
			&self->room->burnout_state, self->room->inputs->time_to_burnout);
		fprintf(stdout, "\t%i coder_burnout res %i\n", self->id, res);
		fflush(stdout);

		if (!(res != 110))
		{
			pthread_mutex_lock(&self->room->print_m);
			fprintf(stdout, "%llu %i Burned Out!\n", get_time_past(self->room->start_time), self->id);
			fflush(stdout);
			pthread_mutex_unlock(&self->room->print_m);
			pthread_mutex_lock(&self->room->burnout_m);
			self->room->burnout_state = 1;
			pthread_mutex_unlock(&self->room->burnout_m);
			ft_out(self->room, NULL, 1, "A coder has burned out! Simulation ending.");
		}
	}
	return (NULL);
}

void	*coder_funct(void *input_raw)
{
	t_coder	*self;

	self = (t_coder *) input_raw;
	// printf("burnout %i\n", self->room->burnout_state);
	fprintf(stderr, "Hello from coder thread %i!\n", self->id);
	pthread_mutex_lock(&self->room->print_m);
	pthread_create(&self->burnout_thread, NULL, coder_burnout, self);
	fprintf(stderr, "Coder %i Stat!\n", self->id);
	pthread_mutex_unlock(&self->room->print_m);
	// printf("burnout %i\n", self->room->burnout_state);
	if (!(self->id % 2))
		msleep(5);
	do_compile(self);
	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& !self->room->burnout_state)
	{
		// printf("burnout %i\n", self->room->burnout_state);
		do_debug(self);
		do_refactor(self);
		// printf("burnout %i\n", self->room->burnout_state);
		do_compile(self);
	}
	fprintf(stderr, "Coder %i is Finished!\n", self->id);
	return (NULL);
}
