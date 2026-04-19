/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/19 23:12:31 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_out(t_programming_room *room, int *temp, int code, char *msg)
{
	int coder_id;

	if (room)
	{
		coder_id = -1;
		while (++coder_id < room->inputs->number_of_coders)
			pthread_join(room->coders[coder_id].thread, NULL);
		coder_id = 0;
		while (coder_id < room->inputs->number_of_coders)
		{
			pthread_mutex_destroy(&room->dongles[coder_id].mutex);
			pthread_cond_destroy(&room->dongles[coder_id].state);
			coder_id++;
		}
		trash(room->coders);
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

void init_id(t_programming_room *room, int coder_id)
{
		room->coders[coder_id].id = coder_id;
		room->coders[coder_id].room = room;
		room->coders[coder_id].last_compile_time = -1;
		room->coders[coder_id].compilations_complete = 0;
		room->coders[coder_id].burnout_timer = room->inputs->time_to_burnout;
		room->coders[coder_id].dongle_l = &room->dongles[coder_id];
		room->coders[coder_id].dongle_r = &room->dongles[(coder_id + 1) % (room->inputs->number_of_coders)];
		pthread_create(&room->coders[coder_id].thread, NULL, coder_funct, &room->coders[coder_id]);
		room->dongles[coder_id].id = coder_id;
		room->dongles[coder_id].dongle_cooldown = room->inputs->dongle_cooldown;
		pthread_mutex_init(&(room->dongles[coder_id].mutex), NULL);
		pthread_cond_init(&(room->dongles[coder_id].state), NULL);
}

void	prep_room(t_programming_room *room)
{
	int	coder_id;

	pthread_mutex_init(&(room->start_sim_m), NULL);
	pthread_cond_init(&(room->start_sim_c), NULL);
	pthread_mutex_init(&(room->pause_m), NULL);
	pthread_cond_init(&(room->pause_c), NULL);
	pthread_mutex_init(&(room->burnout_m), NULL);
	pthread_cond_init(&(room->burnout_c), NULL);
	room->burnout_state = 0;
	room->coders = malloc(sizeof(t_coder) * (room->inputs->number_of_coders));
	room->dongles = malloc(sizeof(t_dongle) * (room->inputs->number_of_coders));
	coder_id = 0;
	while (coder_id < room->inputs->number_of_coders)
	{
		fprintf(stderr, "\tLoop %i!\n", coder_id);
		fflush(stdout);
		init_id(room,coder_id );
		fprintf(stderr, "\tEnd Loop %i!\n", coder_id);
		fflush(stdout);
		coder_id++;
	}
}

		// pthread_create(&(room->dongles[coder_id].thread), NULL, dongle_funct, &room);
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
	// input = get_inputs();

/*
 0	- fifo means First In, First Out: the dongle is granted to the coder whose
request arrived first.
 1	-edf means Earliest Deadline First with deadline = last_compile_start +
time_to_burnout.
*/

int	main(int argc, char *argv[])
{
	t_programming_room	room;

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

	prep_room(&room);

	fprintf(stderr, "\tRoom Prepped!\n");
	fflush(stdout);

	gettimeofday(room.start_time, NULL);
	// pthread_cond_broadcast(&room.start_sim_c);

	fprintf(stderr, "\tLET THE GAMES BEGIN!\n");
	fflush(stdout);

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
