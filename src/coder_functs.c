/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/06/26 19:02:37 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_compile(t_coder *self)
{
	fprintf(stderr, "C%i in Compile\n", self->id);
	if (check_burnout(self->room))
		return ;
	take_dongles(self);
	if (check_burnout(self->room))
	{
		fprintf(stderr,
			"C%i exits compilation prematurely\n", self->id);
		free_dongles(self);
		return ;
	}
	pthread_mutex_lock(&self->compiling_m);
	pthread_cond_broadcast(&self->compiling_c);
	self->last_ct = print_event(self->room->start_time, self->id,
			"is compiling", &self->room->print_m);
	self->compilations_complete += 1;
	pthread_mutex_unlock(&self->compiling_m);
	safe_msleep(self->room->inputs->time_to_compile, self->room);
	free_dongles(self);
}

static void	do_compile_loop(t_coder *self)
{
	if (check_burnout(self->room))
		return ;
	print_event(self->room->start_time, self->id, "is debugging",
		&self->room->print_m);
	safe_msleep(self->room->inputs->time_to_debug, self->room);
	if (check_burnout(self->room))
		return ;
	print_event(self->room->start_time, self->id, "is refactoring",
		&self->room->print_m);
	safe_msleep(self->room->inputs->time_to_refactor, self->room);
	do_compile(self);
}

static void	wait_for_burnout(t_coder *self)
{
	struct timespec	timeout;
	int				res;

	res = 0;
	pthread_mutex_lock(&self->compiling_m);
	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& !check_burnout(self->room) && !res)
	{
		timeout = get_timespec_offset(self->room->inputs->time_to_burnout);
		if (!check_burnout(self->room))
			res = pthread_cond_timedwait(&self->compiling_c,
					&self->compiling_m, &timeout);
		fprintf(stderr, "\tCB%i Broadcast Status: %i bo: %i done: %i, total: %i\n",
			self->id, !res, !check_burnout(self->room), self->compilations_complete
		< self->room->inputs->number_of_compiles_required,
		(self->compilations_complete < self->room->inputs->number_of_compiles_required
		&& !check_burnout(self->room) && !res));
	}
	pthread_mutex_unlock(&self->compiling_m);
}

// static void	wait_for_burnout(t_coder *self)
// {
// 	int				res;

// 	res = 0;
// 	pthread_mutex_lock(&self->compiling_m);
// 	while (self->compilations_complete
// 		< self->room->inputs->number_of_compiles_required
// 		&& !check_burnout(self->room) && !res)
// 	{
// 		pthread_mutex_unlock(&self->compiling_m);
// 		res = safe_cond_timedwait(&self->compiling_c, &self->compiling_m,
// 				self->room->inputs->time_to_burnout, self->room);
// 		fprintf(stderr, "\tCB%i Broadcast Status: %i bo: %i done: %i, total: %i\n",
// 			self->id, !res, !check_burnout(self->room), self->compilations_complete
// 		< self->room->inputs->number_of_compiles_required,
// 		(self->compilations_complete < self->room->inputs->number_of_compiles_required
// 		&& !check_burnout(self->room) && !res));
// 		pthread_mutex_lock(&self->compiling_m);
// 	}
// 	pthread_mutex_unlock(&self->compiling_m);
// }

void	*coder_burnout(void *input_raw)
{
	t_coder	*self;

	self = (t_coder *) input_raw;
	fprintf(stderr, "Starting CB%i\n", self->id);
	safe_mod_val_int(&self->b_ready, DONE, &self->room->ready_m);
	safe_cond_timedwait(&self->room->start_sim_c, &self->room->start_sim_m,
		power(self->room->inputs->number_of_coders, 3) + 200, self->room);
	wait_for_burnout(self);
	pthread_mutex_lock(&self->room->burnout_m);
	if (self->room->burnout_state == ACTIVE && self->compilations_complete
		!= self->room->inputs->number_of_compiles_required)
	{
		print_event(self->room->start_time, self->id, "burned out",
			&self->room->print_m);
		self->room->burnout_state = DONE;
	}
	pthread_mutex_unlock(&self->room->burnout_m);
	fprintf(stderr, "\t\tCB%i is done\n", self->id);
	return (NULL);
}

void	*coder_funct(void *input_raw)
{
	t_coder	*self;

	self = (t_coder *)input_raw;
	fprintf(stderr, "Hello from C%i thread!\n", self->id);
	pthread_create(&self->burnout_thread, NULL, coder_burnout, self);
	safe_mod_val_int(&self->c_ready, DONE, &self->room->ready_m);
	// safe_cond_timedwait(&self->room->start_sim_c, &self->room->start_sim_m,
	// 	power(self->room->inputs->number_of_coders, 3) + 200, self->room);
	safe_cond_wait(&self->room->start_sim_c, &self->room->start_sim_m,
		self->room);
	fprintf(stderr, "C%i Stat!\n", self->id);
	if (!(self->id % 2))
		safe_msleep(self->room->inputs->time_to_compile - 20, self->room);
	do_compile(self);
	pthread_mutex_lock(&self->compiling_m);
	fprintf(stderr, "C%i out Compile: pre-loop bo: %i\n",
		self->id, self->room->burnout_state);
	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& !check_burnout(self->room))
	{
		pthread_mutex_unlock(&self->compiling_m);
		fprintf(stderr, "  Compiles Complete by C%i: %i\n",
			self->id, self->compilations_complete);
		do_compile_loop(self);
		fprintf(stderr, "C%i out Compile\n", self->id);
		pthread_mutex_lock(&self->compiling_m);
	}
	fprintf(stderr, "\t\tC%i is Finished! bo: %i\n",
		self->id, self->room->burnout_state);
	pthread_mutex_unlock(&self->compiling_m);
	fprintf(stderr, "C%i Waiting for Burnout_thread\n", self->id);
	pthread_join(self->burnout_thread, NULL);
	fprintf(stderr, "\t\tBurnout C%i Done\n", self->id);
	fflush(stderr);
	return (NULL);
}
