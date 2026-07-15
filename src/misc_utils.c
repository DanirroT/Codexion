/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 14:54:49 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/06/26 17:27:30 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_do_atoi_strict_pos(char **arg,
	int rep, int *temp, t_programming_room *room)
{
	int			i;
	long long	num;

	num = 0;
	i = 0;
	while (ft_isdigit(arg[rep][i]))
	{
		if ((num * 10 + (arg[rep][i] - '0')) > INT_MAX)
			return (printf("Error: Number out of range. Must be between"
					" 0 and 2147483647."), ft_out(room, temp, 2));
		num = num * 10 + (arg[rep][i] - '0');
		i++;
	}
	return ((int)num);
}

int	check_burnout(t_programming_room *room)
{
	pthread_mutex_lock(&room->burnout_m);
	if (room->burnout_state == DONE
		|| room->complete_state == DONE)
	{
		pthread_mutex_unlock(&room->burnout_m);
		return (1);
	}
	pthread_mutex_unlock(&room->burnout_m);
	return (0);
}

long long	print_event(struct timeval start_time, int id,
	char *msg, pthread_mutex_t *mutex)
{
	long long	time_past;

	time_past = get_time_past(start_time);
	pthread_mutex_lock(mutex);
	printf("%llu %i %s\n", time_past, id, msg);
	fprintf(stderr, "\t----- %llu %i %s -----\n", time_past, id, msg);
	pthread_mutex_unlock(mutex);
	return (time_past);
}



// int main(int argc, char const *argv[])
// {
// 	t_programming_room room;

// 	pthread_mutex_init(&room.burnout_m, NULL);
// 	room.burnout_state = ACTIVE;
// 	room.complete_state = ACTIVE;
// 	printf("%i\n", check_burnout(&room));
// 	return 0;
// }
