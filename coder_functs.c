/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/19 23:03:18 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	do_compile(t_coder *self)
{
	long long	start_time;

	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli %i is compiling\n", start_time, self->id);
	fflush(stdout);
	self->last_compile_time = start_time;
	usleep(self->room->inputs->time_to_compile);

}

void	do_debug(t_coder *self)
{
	long long	start_time;

	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli %i is debugging\n", start_time, self->id);
	fflush(stdout);
	usleep(self->room->inputs->time_to_debug);

}

void	do_refactor(t_coder *self)
{
	long long	start_time;

	start_time = get_time_past(self->room->start_time);
	fprintf(stdout, "%lli %i is refactoring\n", start_time, self->id);
	fflush(stdout);

	usleep(self->room->inputs->time_to_refactor);
}
void	take_dongles(t_coder *self)
{
	int				result;

	result = 1;
	while(result)
	{
		pthread_mutex_lock(&self->dongle_l->mutex);
		fprintf(stdout, "%lli %i has taken a dongle %i\n", get_time_past(self->room->start_time), self->id, self->dongle_l->id);
		fflush(stdout);

		result = cond_timedwait(&(self->dongle_r)->state, &(self->dongle_r)->mutex, &self->room->burnout_state, 50);
		if (!result)
		{
			pthread_mutex_lock(&self->dongle_r->mutex);
			fprintf(stdout, "%lli %i has taken a dongle %i\n", get_time_past(self->room->start_time), self->id, self->dongle_r->id);
			fflush(stdout);
		}
		else
		{
			pthread_mutex_unlock(&self->dongle_l->mutex);
			fprintf(stdout, "%lli %i has let go of a dongle %i\n", get_time_past(self->room->start_time), self->id, self->dongle_l->id);
			usleep(50);
		}
	}
}

/*
	while (ready != 0)
	{
		gettimeofday(&loop_time, NULL);

		loop_time.tv_usec += 50;
		cond_timedwait(&room->dongles[self->dongle_r].state, &room->dongles[self->dongle_r].mutex, &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_r]);
		fprintf(stdout, "%lli %i has taken a dongle\n", loop_time, self->id);
		fflush(stdout);

		loop_time.tv_usec += 50;
		cond_timedwait(&room->dongles[self->dongle_l].state, &room->dongles[self->dongle_l].mutex, &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_l]);
		fprintf(stdout, "%lli %i has taken a dongle\n", loop_time, self->id);
		fflush(stdout);
	}
*/

void	*dongle_cooldown(void *input_raw)
{
	t_dongle	*dongle;

	dongle = (t_dongle *)input_raw;

	usleep(dongle->dongle_cooldown);

	// cond_timedwait(&dongle->state,
	// 	&dongle->mutex, 50);
	pthread_mutex_unlock(&dongle->mutex);
	pthread_cond_broadcast(&dongle->state);
	return (NULL);
}

void	free_dongles(t_coder *self)
{
	pthread_t	dongle_l;
	pthread_t	dongle_r;

	pthread_create(&dongle_l, NULL, dongle_cooldown, self->dongle_l);
	pthread_create(&dongle_r, NULL, dongle_cooldown, self->dongle_r);
}

void	*coder_funct(void *input_raw)
{
	t_coder				*self;

	self = (t_coder *)input_raw;

	fprintf(stderr, "Hello from coder thread %i!\n", self->id);
	fflush(stdout);

	cond_wait(&self->room->start_sim_c, &self->room->start_sim_m, &self->room->burnout_state);

	fprintf(stderr, "\tSTART %i!\n", self->id);
	fflush(stdout);

	take_dongles(self);
	do_compile(self);
	free_dongles(self);
	while (self->compilations_complete > self->room->inputs->number_of_compiles_required)
	{
		do_debug(self);
		do_refactor(self);
		take_dongles(self);
		do_compile(self);
		free_dongles(self);
	}
	return (NULL);
}
