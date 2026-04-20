/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 20:45:47 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/20 17:29:35 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_isitoa(int c)
{
	return (ft_isspace(c) || ft_isdigit(c)
		|| c == '+' || c == '-');
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

int	ft_isspace(int c)
{
	return ((c == ' ' || (c >= 9 && c <= 13)));
}

long long	get_time_past(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - start.tv_sec) * 1000LL + (now.tv_usec
			- start.tv_usec) / 1000LL);
}

struct timespec get_timespec_offset(int offset)
{
	struct timespec timespec_time;
	struct timeval	timeval_time;

	gettimeofday(&timeval_time, NULL);

	timespec_time.tv_sec = timeval_time.tv_sec;
	timespec_time.tv_nsec = (timeval_time.tv_usec + offset) / 1000;
	return (timespec_time);
}

int cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex, int *condition)
{
	int result;

	pthread_mutex_lock(mutex);
	while (!*condition)
		result = pthread_cond_wait(cond, mutex);
	pthread_mutex_unlock(mutex);
	return (result);
}

int cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, int *condition, int delay)
{
	int result;
	struct timespec timespec_time;

	timespec_time = get_timespec_offset(delay);

	pthread_mutex_lock(mutex);
	while (!*condition)
	{
		result = pthread_cond_timedwait(cond, mutex, &timespec_time);
		if (result)
			break;
	}
	pthread_mutex_unlock(mutex);
	return (result);
}

int msleep(int wait)
{
	return (usleep(wait * 1000));
}
