/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/29 20:43:20 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/06/25 19:20:57 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

// void	safe_add_val_int(int *var, int val, pthread_mutex_t *mutex)
// {
// 	pthread_mutex_lock(mutex);
// 	*var += val;
// 	pthread_mutex_unlock(mutex);
// }

void	safe_mod_val_int(int *var, int val, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	*var = val;
	pthread_mutex_unlock(mutex);
}

void	safe_broadcast(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	pthread_cond_broadcast(cond);
	fprintf(stderr, "\tBroadcast %p (%p)\n", cond, mutex);
	pthread_mutex_unlock(mutex);
}

void	safe_cond_wait(pthread_cond_t *cond,
	pthread_mutex_t *mutex, t_programming_room *room)
{
	pthread_mutex_lock(mutex);
	fprintf(stderr, "waiting %p (%p): %i %i\n", cond, mutex,
		room->burnout_state, ACTIVE);
	fflush(stderr);
	if (!check_burnout(room))
		pthread_cond_wait(cond, mutex);
	pthread_mutex_unlock(mutex);
}

int	safe_cond_timedwait(pthread_cond_t *cond,
	pthread_mutex_t *mutex, int offset, t_programming_room *room)
{
	struct timespec	timeout;
	int				out;

	timeout = get_timespec_offset(offset);
	pthread_mutex_lock(mutex);
	fprintf(stderr, "waiting %p (%p): %i %i for %ims\n", cond, mutex,
		room->burnout_state, ACTIVE, offset);
	out = 0;
	if (!check_burnout(room))
		out = pthread_cond_timedwait(cond, mutex, &timeout);
	pthread_mutex_unlock(mutex);
	return (out);
}
