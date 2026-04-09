/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/09 15:15:04 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	do_compile(t_coder *self, t_programming_room *room)
{
	long long	start_time;

	start_time = get_time_past(&room->start_time);
	fprintf(stdout, "%lli %i is compiling\n", start_time, self->id);
	fflush(stdout);
	self->last_compile_time = start_time;
	usleep(room->inputs->time_to_compile);

}

void	do_debugg(t_coder *self, t_programming_room *room)
{
	long long	start_time;

	start_time = get_time_past(&room->start_time);
	fprintf(stdout, "%lli %i is debugging\n", start_time, self->id);
	fflush(stdout);
	usleep(room->inputs->time_to_debug);

}

void	do_refactor(t_coder *self, t_programming_room *room)
{
	long long	start_time;

	start_time = get_time_past(&room->start_time);
	fprintf(stdout, "%lli %i is refactoring\n", start_time, self->id);
	fflush(stdout);

	usleep(room->inputs->time_to_refactor);

}

void	take_dongles(t_coder *self, t_programming_room *room)
{
	long long	loop_time;
	int			ready;

	ready = 2;
	while (ready != 0)
	{
		loop_time = get_time_past(&room->start_time);

		loop_time += 50;
		pthread_cond_timedwait(&room->dongles[self->dongle_r].state, &room->dongles[self->dongle_r].mutex, &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_r]);
		fprintf(stdout, "%lli %i has taken a dongle\n", loop_time, self->id);
		fflush(stdout);

		loop_time += 50;
		pthread_cond_timedwait(&room->dongles[self->dongle_l].state, &room->dongles[self->dongle_l].mutex, &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_l]);
		fprintf(stdout, "%lli %i has taken a dongle\n", loop_time, self->id);
		fflush(stdout);
	}
}

void	dongle_cooldown(void *input_raw)
{
	long long	cooldown_time;
	t_dongle	*dongle;

	dongle = (t_dongle *)input_raw;

	cooldown_time = get_time_past(NULL);
	cooldown_time += dongle->dongle_cooldown;

	pthread_cond_timedwait(&dongle->state,
		&dongle->mutex, &cooldown_time);
	pthread_mutex_unlock(&dongle->mutex);
}

void	free_dongles(t_programming_room *room, int index_l, int index_r)
{
	pthread_t	dongle_l;
	pthread_t	dongle_r;

	pthread_create(&dongle_l, NULL, dongle_cooldown, &room->dongles[index_l]);
	pthread_create(&dongle_r, NULL, dongle_cooldown, &room->dongles[index_r]);
}

void	*coder_funct(void *input_raw)
{
	t_programming_room	*room;
	t_coder				self;

	room = (t_programming_room *)input_raw;

	fprintf(stderr, "Hello from coder thread %i!\n", self.id);

	pthread_cond_broadcast(&room->pause_c);

	pthread_cond_wait(&room->start_sim_c, &room->start_sim_m);

	take_dongles(&self, room);
	do_compile(&self, room);
	free_dongles(room, self.dongle_r, self.dongle_l);
	while (self.compilations_complete > room->inputs->number_of_compiles_required)
	{
		do_debugg(&self, room);
		do_refactor(&self, room);
		take_dongles(&self, room);
		do_compile(&self, room);
		free_dongles(room, self.dongle_r, self.dongle_l);
	}
	return (NULL);
}
