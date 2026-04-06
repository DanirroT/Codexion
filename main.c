/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/06 18:21:28 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_out(t_programming_room *room, int *temp, int code, char *msg)
{
	if (room)
	{
		while (room->inputs->number_of_coders)
		{
			pthread_join(*room->coders, NULL);
			room->inputs->number_of_coders--;
			pthread_mutex_destroy(room->dongles);
			pthread_cond_destroy(room->dongles_state);
		}
		trash(room->coders);
		trash(room->dongles);
		trash(room->dongles_state);
		trash(room->inputs);
	}
	trash(temp);
	if (msg)
		fprintf(stderr, "%s\n", msg);
	if (code)
		exit(code);
	return (code);
}

void	create_coders(t_programming_room *room, int number_of_coders)
{
	room->coders = malloc(sizeof(pthread_t) * number_of_coders);
	room->dongles = malloc(sizeof(pthread_mutex_t) * number_of_coders);
	room->dongles_state = malloc(sizeof(pthread_cond_t) * number_of_coders);
}

void	do_compile(t_coder *self, t_programming_room *room)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	fprintf(stdout, "%li %i is compiling\n", start_time.tv_usec, self->id);
	self->last_compile_time = start_time.tv_usec;
	usleep(room->inputs->time_to_compile);

}

void	do_debugg(t_coder *self, t_programming_room *room)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	fprintf(stdout, "%li %i is debugging\n", start_time.tv_usec, self->id);
	usleep(room->inputs->time_to_debug);

}

void	do_refactor(t_coder *self, t_programming_room *room)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	fprintf(stdout, "%li %i is refactoring\n", start_time.tv_usec, self->id);
	usleep(room->inputs->time_to_refactor);

}

void	take_dongles(t_coder *self, t_programming_room *room)
{
	struct timeval	loop_time;
	int ready;

	ready = 2;
	while (ready != 0)
	{
		gettimeofday(&loop_time, NULL);

		loop_time.tv_sec += 5;
		loop_time.tv_usec += 5;
		pthread_cond_timedwait(&room->dongles_state[self->dongle_r], &room->dongles[self->dongle_r], &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_r]);
		fprintf(stdout, "%li %i has taken a dongle\n", loop_time.tv_usec, self->id);

		loop_time.tv_sec += 5;
		loop_time.tv_usec += 5;
		pthread_cond_timedwait(&room->dongles_state[self->dongle_l], &room->dongles[self->dongle_l], &loop_time);
		pthread_mutex_lock(&room->dongles[self->dongle_l]);
		fprintf(stdout, "%li %i has taken a dongle\n", loop_time.tv_usec, self->id);
	}
}

void	free_dongles(t_programming_room *room, int index_l, int index_r)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	start_time.tv_sec += room->inputs->dongle_cooldown;
	start_time.tv_usec += room->inputs->dongle_cooldown;

	pthread_cond_timedwait(&room->dongles_state[index_l], NULL, &start_time);
	pthread_mutex_unlock(&room->dongles[index_l]);
	pthread_mutex_unlock(&room->dongles[index_r]);
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

	create_coders(&room, room.inputs->number_of_coders);

	// printf("start_time: %li\n", room.inputs->start_time);
	room.iter = 1;
	while (room.iter <= room.inputs->number_of_coders)
	{
		pthread_create(&(room.coders[room.iter]), NULL, coder_funct, &room);
		pthread_mutex_init(&(room.dongles[room.iter]), NULL);
		pthread_cond_init(&(room.dongles_state[room.iter]), NULL);
		room.iter++;
	}
	gettimeofday(&room.start_time, NULL);

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
