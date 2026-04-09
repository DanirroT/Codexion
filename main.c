/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/09 15:16:53 by dmota-ri         ###   ########.fr       */
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
		trash(room->inputs);
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
	int	i;

	room->coder_threads = malloc(sizeof(pthread_t) * (len + 1));
	room->coders = malloc(sizeof(t_coder) * (len + 1));
	room->dongle_threads = malloc(sizeof(pthread_t) * (len + 1));
	room->dongles = malloc(sizeof(t_dongle) * (len + 1));
	i = 1;
	while (i <= len)
	{
		room->coders[i].id = i;
		room->coders[i].last_compile_time = -1;
		room->coders[i].compilations_complete = 0;
		room->coders[i].burnout_timer = room->inputs->time_to_burnout;
		room->coders[i].dongle_l = i;
		room->coders[i].dongle_r = (i + 1) % (len + 1);
		room->dongles[i].id = i;
		room->dongles[i].dongle_cooldown = room->inputs->dongle_cooldown;
		i++;
	}
	pthread_mutex_init(&room->start_sim_m, NULL);
	pthread_cond_init(&room->start_sim_c, NULL);
	pthread_mutex_init(&room->pause_m, NULL);
	pthread_cond_init(&room->pause_c, NULL);
	pthread_mutex_init(&room->burnout_m, NULL);
	pthread_cond_init(&room->burnout_c, NULL);
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
	int					i;

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
	i = 0;
	while (i <= room.inputs->number_of_coders)
	{
		pthread_create(&(room.coder_threads[i]), NULL, coder_funct, &room);
		// pthread_create(&(room.dongle_threads[i]), NULL, dongle_funct, &room);
		pthread_mutex_init(&(room.dongles[i].mutex), NULL);
		pthread_cond_init(&(room.dongles[i].state), NULL);
		pthread_cond_wait(&room.pause_c, &room.pause_m);
		i++;
	}

	gettimeofday(&room.start_time, NULL);
	pthread_cond_broadcast(&room.start_sim_c);

	return (ft_out(&room, NULL, 0, "Simulation ended successfully."));
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
