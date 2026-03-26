/* ************************************************************************** */
/*                                                                            */
/*                                                       :::      ::::::::    */
/*   main.c                                            :+:      :+:    :+:    */
/*                                                   +:+ +:+         +:+      */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com>  #+#  +:+       +#+         */
/*                                               +#+#+#+#+#+   +#+            */
/*   Created: 2026/03/25 19:40:31 by dmota-ri         #+#    #+#              */
/*   Updated: 2026/03/26 14:44:50 by dmota-ri        ###   ########.fr        */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void create_coders(pthread_t * coders, pthread_mutex_t * dongles,
	pthread_cond_t	*dongles_state, int number_of_coders)
{
	*coders = malloc(sizeof(pthread_t) * number_of_coders);
	*dongles = malloc(sizeof(pthread_mutex_t) * number_of_coders);
	*dongles_state = malloc(sizeof(pthread_cond_t) * number_of_coders);
}

int	coder_funct(t_inpt_args input)
{
}

int	main(int argc, char *argv[])
{
	pthread_t		*coders;
	pthread_mutex_t	*dongles;
	pthread_cond_t	*dongles_state;
	t_inpt_args		input;
	int				i;

	input
	create_coders(coders, dongles, dongles_state, input.number_of_coders);
	gettimeofday(&input.start_time, NULL);
	i = 0;
	while (i < input.number_of_coders)
	{
		pthread_create(&(coders[i]), NULL, coder_funct, input);
		pthread_mutex_init(&(dongles[i]), NULL);
		pthread_cond_init(&(dongles_state[i]), NULL);
	}
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
