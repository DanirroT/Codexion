/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/22 14:26:41 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_coder(t_programming_room *room, int id)
{
	room->coders[id].id = id + 1;
	room->coders[id].c_ready = ACTIVE;
	room->coders[id].room = room;
	room->coders[id].compilations_complete = 0;
	room->coders[id].last_ct = 0;
	room->coders[id].dongle_l = &room->dongles[id];
	room->coders[id].dongle_r = &room->dongles[(id + 1)
		% (room->inputs->number_of_coders)];
	pthread_mutex_init(&room->coders[id].compiling_m, NULL);
	pthread_create(&room->coders[id].thread, NULL,
		coder_funct, &room->coders[id]);
}

static void	init_dongle(t_programming_room *room, int id)
{
	room->dongles[id].queue = NULL;
	room->dongles[id].id = id + 1;
	room->dongles[id].d_ready = ACTIVE;
	room->dongles[id].room = room;
	pthread_mutex_init(&(room->dongles[id].state_m), NULL);
	pthread_cond_init(&(room->dongles[id].take), NULL);
	pthread_cond_init(&(room->dongles[id].free), NULL);
	pthread_cond_init(&(room->dongles[id].ready), NULL);
	room->dongles[id].state = HELD;
	pthread_create(&room->dongles[id].thread, NULL,
		dongle_funct, &room->dongles[id]);
}

static int	prep_room(t_programming_room *room)
{
	int	id;

	pthread_mutex_init(&(room->burnout_m), NULL);
	pthread_mutex_init(&room->print_m, NULL);
	pthread_mutex_lock(&room->print_m);
	pthread_mutex_init(&room->ready_m, NULL);
	pthread_mutex_init(&room->start_sim_m, NULL);
	pthread_cond_init(&room->start_sim_c, NULL);
	room->burnout_state = ACTIVE;
	room->complete_state = ACTIVE;
	room->dongles = malloc((size_t)(sizeof(t_dongle)
				* (room->inputs->number_of_coders)));
	if (!room->dongles)
		return (DONE);
	id = -1;
	while (++id < room->inputs->number_of_coders)
		init_dongle(room, id);
	room->coders = malloc((size_t)(sizeof(t_coder)
				* (room->inputs->number_of_coders)));
	if (!room->coders)
		return (DONE);
	id = -1;
	while (++id < room->inputs->number_of_coders)
		init_coder(room, id);
	pthread_create(&room->burnout_thread, NULL,
		coder_burnout, room);
	return (ACTIVE);
}

static void	wait_all_ready(t_programming_room *room, int out, int i)
{
	msleep(room->inputs->number_of_coders);
	while (1)
	{
		out = 0;
		while (i < room->inputs->number_of_coders)
		{
			pthread_mutex_lock(&room->ready_m);
			if (room->coders[i].c_ready == ACTIVE
				|| room->dongles[i].d_ready == ACTIVE)
			{
				out = 1;
				pthread_mutex_unlock(&room->ready_m);
				break ;
			}
			pthread_mutex_unlock(&room->ready_m);
			i++;
		}
		if (out == 0)
			break ;
		msleep(room->inputs->number_of_coders - i);
	}
	while (1)
	{
		pthread_mutex_lock(&room->ready_m);
		if (room->b_ready == DONE)
		{
			pthread_mutex_unlock(&room->ready_m);
			break ;
		}
		pthread_mutex_unlock(&room->ready_m);
		msleep(2);
	}
	msleep(room->inputs->number_of_coders);
}

int	main(int argc, char *argv[])
{
	t_programming_room	*room;

	argc += 1;
	room = malloc(sizeof(t_programming_room));
	if (!room)
		return (ft_out(NULL, NULL, -1));
	memset(room, 0, sizeof(t_programming_room));
	if (parse_args_inputs(argv, room) == DONE
		|| prep_room(room) == DONE)
		return (ft_out(room, NULL, -1));
	wait_all_ready(room, 0, 0);
	gettimeofday(&room->start_time, NULL);
	pthread_mutex_unlock(&room->print_m);
	safe_broadcast(&room->start_sim_c, &room->start_sim_m);
	return (ft_out(room, NULL, 0));
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
