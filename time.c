/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:55:00 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/04/21 19:01:33 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	msleep(int wait)
{
	if (wait == -1)
		return (usleep((suseconds_t)wait));
	if (wait < 0)
		return (-1);
	return (usleep((suseconds_t)wait * 1000));
}

long long	get_time_past(struct timeval start)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	fprintf(stderr, "get_time_past: now %lu.%lu start %lu.%lu\n%lu.%lu -> %llu\n\n",
		now.tv_sec, now.tv_usec, start.tv_sec, start.tv_usec,
		now.tv_sec - start.tv_sec, now.tv_usec - start.tv_usec,
		(now.tv_sec - start.tv_sec) * 1000LL + (now.tv_usec - start.tv_usec) / 1000LL);
	return ((now.tv_sec - start.tv_sec) * 1000LL
			+ (now.tv_usec - start.tv_usec) / 1000LL);
}

struct timespec	get_timespec_offset(int offset)
{
	struct timespec	timespec_time;
	struct timeval	timeval_time;

	gettimeofday(&timeval_time, NULL);
	timespec_time.tv_sec = timeval_time.tv_sec;
	timespec_time.tv_nsec = (timeval_time.tv_usec + offset) / 1000;
	return (timespec_time);
}
