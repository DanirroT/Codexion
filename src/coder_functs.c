/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_functs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 15:09:17 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/20 13:57:06 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_compile(t_coder *self)
{
	fprintf(stderr, "%llu C%i: in Compile\n",
		get_time_past(self->room->start_time), self->id);
	if (check_burnout(self->room))
		return ;
	take_dongles(self);
	if (check_burnout(self->room))
	{
		fprintf(stderr, "%llu C%i: exits compilation prematurely\n",
			get_time_past(self->room->start_time), self->id);
		free_dongles(self);
		return ;
	}
	pthread_mutex_lock(&self->compiling_m);
	self->last_ct = print_event(self->room, self->id, "is compiling");
	self->compilations_complete += 1;
	pthread_mutex_unlock(&self->compiling_m);
	safe_msleep(self->room->inputs->time_to_compile, self->room);
	free_dongles(self);
}

static void	do_compile_loop(t_coder *self)
{
	print_event(self->room, self->id, "is debugging");
	safe_msleep(self->room->inputs->time_to_debug, self->room);
	print_event(self->room, self->id, "is refactoring");
	safe_msleep(self->room->inputs->time_to_refactor, self->room);
	do_compile(self);
}

void	*coder_funct(void *input_raw)
{
	t_coder	*self;

	self = (t_coder *)input_raw;
	fprintf(stderr, "Hello from C%i thread!\n", self->id);
	safe_mod_val_int(&self->c_ready, DONE, &self->room->ready_m);
	safe_cond_timedwait(&self->room->start_sim_c, &self->room->start_sim_m,
		power(self->room->inputs->number_of_coders, 3) + 200, self->room);
	// safe_cond_wait(&self->room->start_sim_c, &self->room->start_sim_m,
	// 	self->room);
	fprintf(stderr, "%llu C%i: Stat!\n",
		get_time_past(self->room->start_time), self->id);
	if (!(self->id % 2))
		safe_msleep(self->room->inputs->time_to_compile - 20, self->room);
	do_compile(self);
	pthread_mutex_lock(&self->compiling_m);
	fprintf(stderr, "%llu C%i: out Compile\n",
		get_time_past(self->room->start_time), self->id);
	while (self->compilations_complete
		< self->room->inputs->number_of_compiles_required
		&& !check_burnout(self->room))
	{
		pthread_mutex_unlock(&self->compiling_m);
		fprintf(stderr, "  Compiles Complete by C%i: %i\n",
			self->id, self->compilations_complete);
		do_compile_loop(self);
		fprintf(stderr, "%llu C%i: out Compile\n",
			get_time_past(self->room->start_time), self->id);
		pthread_mutex_lock(&self->compiling_m);
	}
	fprintf(stderr, "\t\tC%i is Finished!\n", self->id);
	pthread_mutex_unlock(&self->compiling_m);
	fprintf(stderr, "%llu C%i: END!\n",
		get_time_past(self->room->start_time), self->id);
	fflush(stderr);
	return (NULL);
}
