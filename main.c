/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/02 21:01:04 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_out(t_input_args *args, int *temp, int code, char *msg)
{
	trash(args);
	trash(temp);
	if (msg)
		printf("%s\n", msg);
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

void	*coder_funct(void *input_raw)
{
	t_input_args *input;

	input = (t_input_args *)input_raw;

	printf("Hello from coder thread!\n%li", input->start_time.tv_sec);
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
	t_input_args		*input;
	int					i;

	// input = get_inputs();
	input = parse_args_inputs(argc, argv);

	// printf("Number of coders: %i\n", input->number_of_coders);
	// printf("Time to burnout: %i\n", input->time_to_burnout);
	// printf("Time to compile: %i\n", input->time_to_compile);
	// printf("Time to debug: %i\n", input->time_to_debug);
	// printf("Time to refactor: %i\n", input->time_to_refactor);
	// printf("Number of compiles required: %i\n",
	//		input->number_of_compiles_required);
	// printf("Dongle cooldown: %i\n", input->dongle_cooldown);
	// printf("Scheduler: %i\n", input->scheduler);

	create_coders(&room, input->number_of_coders);
	gettimeofday(&input->start_time, NULL);

	// printf("start_time: %li\n", input->start_time);
	i = 0;
	while (i < input->number_of_coders)
	{
		pthread_create(&(room.coders[i]), NULL, coder_funct, input);
		printf("Created coder thread %i\n", i);
		pthread_mutex_init(&(room.dongles[i]), NULL);
		pthread_cond_init(&(room.dongles_state[i]), NULL);
		i++;
	}

	return ft_out(input, NULL, 0, "Simulation ended successfully.");
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
