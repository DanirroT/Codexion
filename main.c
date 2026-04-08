/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/08 17:00:50 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_out(t_programming_room *room, int *temp, int code, char *msg)
{
	if (room)
	{
		while (room->inputs->number_of_coders)
		{
			pthread_join(*room->coder_threads, NULL);
			pthread_mutex_destroy(&room->dongles[room->inputs->number_of_coders].mutex);
			pthread_cond_destroy(&room->dongles[room->inputs->number_of_coders].state);
			room->inputs->number_of_coders--;
		}
		trash(room->coder_threads);
		trash(room->coders);
		trash(room->dongle_threads);
		trash(room->dongles);
		if (room->inputs)
		{
			trash(room->inputs->scheduler);
			free(room->inputs);
		}
	}
	trash(temp);
	if (msg)
		fprintf(stderr, "%s\n", msg);
	if (code)
		exit(code);
	return (code);
}

void	prep_room(t_programming_room *room, int len)
{
	room->coder_threads = malloc(sizeof(pthread_t) * (len + 1));
	room->coders = malloc(sizeof(t_coder) * (len + 1));

	room->dongle_threads = malloc(sizeof(pthread_t) * (len + 1));
	room->dongles = malloc(sizeof(t_dongle) * (len + 1));

	room->iter = 1;

	pthread_mutex_init(&room->start_sim_m, NULL);
	pthread_cond_init(&room->start_sim_c, NULL);

	pthread_mutex_init(&room->pause_m, NULL);
	pthread_cond_init(&room->pause_c, NULL);
}

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
	int ready;

	ready = 2;
	while (ready != 0)
	{
		loop_time = get_time_past(&room->start_time);

		loop_time += 50;
		pthread_cond_timedwait(&room->dongle[self->dongle_r].state, &room->dongles[self->dongle_r].mutex, &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_r]);
		fprintf(stdout, "%lli %i has taken a dongle\n", loop_time, self->id);
		fflush(stdout);

		loop_time += 50;
		pthread_cond_timedwait(&room->dongle[self->dongle_l].state, &room->dongles[self->dongle_l].mutex, &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_l]);
		fprintf(stdout, "%lli %i has taken a dongle\n", loop_time, self->id);
		fflush(stdout);
	}
}

void	dongle_cooldown(void *input_raw)
{
	long long	cooldown_time;
	t_dongle *dongle;

	dongle = (t_dongle *)input_raw;

	cooldown_time = get_time_past(NULL);
	cooldown_time += room->inputs->dongle_cooldown;

	pthread_cond_timedwait(&room->dongles[room->iter].state,
		&room->dongles[room->iter].mutex, &cooldown_time);
	pthread_mutex_unlock(&room->dongles[room->iter].mutex);
}

void	free_dongles(t_programming_room *room, int index_l, int index_r)
{
	pthread_t dongle_l;
	pthread_t dongle_r;

	pthread_create(&dongle_l, NULL, dongle_cooldown, &room->dongles[index_l]);
	pthread_create(&dongle_r, NULL, dongle_cooldown, &room->dongles[index_r]);
}

void	*coder_funct(void *input_raw)
{
	t_programming_room *room;
	t_coder self;

	room = (t_programming_room *)input_raw;

	self.id = room->iter;
	self.last_compile_time = -1;
	self.burnout_timer = room->inputs->time_to_burnout;

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

/*
t_input_args	*get_inputs()
{
	t_input_args	*input;

	input = malloc(sizeof(t_input_args));
	if (!input)
		return (NULL);

	input->number_of_coders = 5;
	input->time_to_burnout = 1000;
	input->time_to_compile = 200;
	input->time_to_debug = 100;
	input->time_to_refactor = 100;
	input->number_of_compiles_required = 3;
	input->dongle_cooldown = 50;
	input->scheduler = 1;

	return (input);
}
*/

/*
 0	- ERROR
 1	- fifo means First In, First Out: the dongle is granted to the coder whose
request arrived first.
 2	- edf means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

int	main(int argc, char *argv[])
{
	t_programming_room	room;

	// input = get_inputs();
	room.inputs = parse_args_inputs(argc, argv);

	// printf("Number of coders: %i\n", room.inputs->number_of_coders);
	// printf("Time to burnout: %i\n", room.inputs->time_to_burnout);
	// printf("Time to compile: %i\n", room.inputs->time_to_compile);
	// printf("Time to debug: %i\n", room.inputs->time_to_debug);
	// printf("Time to refactor: %i\n", room.inputs->time_to_refactor);
	// printf("Number of compiles required: %i\n",
	//		room.inputs->number_of_compiles_required);
	// printf("Dongle cooldown: %i\n", room.inputs->dongle_cooldown);
	// printf("Scheduler: %i\n", room.inputs->scheduler);

	prep_room(&room, room.inputs->number_of_coders);
	while (room.iter <= room.inputs->number_of_coders)
	{
		pthread_create(&(room.coders[room.iter]), NULL, coder_funct, &room);
		pthread_mutex_init(&(room.dongles[room.iter]), NULL);
		pthread_cond_init(&(room.dongles_state[room.iter]), NULL);
		pthread_cond_wait(&room.pause_c, &room.pause_m);
		room.iter++;
	}

	gettimeofday(&room.start_time, NULL);
	pthread_cond_broadcast(&room.start_sim_c);

	return ft_out(&room, NULL, 0, "Simulation ended successfully.");
}

/*

Core thread functions

int pthread_create(
pthread_t *thread, - where the thread ID will be stored
const pthread_attr_t *attr, - thread attributes (usually NULL)
void *(*start_routine)(void *), - function the thread will run
void *arg - argument passed to that function
) - Creates a Thread

int pthread_join(
pthread_t thread, - thread to wait for
void **retval - where return value goes (or NULL if you don’t care)
) - Waits for a thread to finish.

Mutex (Mutual Exclusion)

pthread_mutex_init(
pthread_mutex_t *mutex, - mutex to initialize
const pthread_mutexattr_t *attr - attributes (usually NULL)
); - Initializes a mutex.

pthread_mutex_lock(
pthread_mutex_t *mutex - the lock you want to acquire
); - Locks the mutex.

pthread_mutex_unlock(
pthread_mutex_t *mutex - the lock you want to release
); - Lets another thread acquire it

pthread_mutex_destroy(
pthread_mutex_t *mutex - mutex to destroy
); - Cleans up the mutex.

Condition Variables (thread coordination)

pthread_cond_init(
pthread_cond_t *cond, - condition variable
const pthread_condattr_t *attr - attributes (usually NULL)
); - Initializes a condition variable.

pthread_cond_wait(
pthread_cond_t *cond, - condition to wait on
pthread_mutex_t *mutex - associated mutex (must already be locked)
); - Waits for a condition.

pthread_cond_timedwait(
pthread_cond_t *cond, - condition variable
pthread_mutex_t *mutex, - associated mutex
const struct timespec *abstime - absolute timeout (NOT relative)
); - Same as pthread_cond_wait, but with a timeout.

pthread_cond_broadcast(
pthread_cond_t *cond - condition variable
); - Wakes all waiting threads.

pthread_cond_destroy(
pthread_cond_t *cond - condition variable
); - Cleans up the condition variable.

int gettimeofday(
struct timeval *restrict tp, - output
void *restrict tzp - ???
); - gets time since EPOC

int usleep(
useconds_t useconds - time to wait
); - makes a thread wait

*/
