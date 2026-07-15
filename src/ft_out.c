/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_out.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 19:40:31 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/06/25 11:28:44 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	out_coders(t_programming_room *room)
{
	int	id;

	if (!room->coders)
		return ;
	id = -1;
	while (++id < room->inputs->number_of_coders)
	{
		fprintf(stderr, "\t\tWaiting for C%i\n", id + 1);
		fflush(stderr);
		pthread_join(room->coders[id].thread, NULL);
		fprintf(stderr, "\t\tMain C%i Done\n", id + 1);
		fflush(stderr);
	}
	safe_mod_val_int(&room->complete_state, DONE, &room->burnout_m);
}

static void	out_dongles(t_programming_room *room)
{
	int	id;

	if (!room->dongles)
		return ;
	id = -1;
	while (++id < room->inputs->number_of_coders)
	{
		fprintf(stderr, "\t\tWaiting for D%i\n", id + 1);
		fflush(stderr);
		pthread_join(room->dongles[id].thread, NULL);
		fprintf(stderr, "\t\tMain D%i Done\n", id + 1);
		fflush(stderr);
		pthread_mutex_destroy(&room->coders[id].compiling_m);
		pthread_cond_destroy(&room->coders[id].compiling_c);
		pthread_cond_destroy(&room->dongles[id].take);
		pthread_cond_destroy(&room->dongles[id].free);
		pthread_cond_destroy(&room->dongles[id].ready);
		ft_lstclear(&room->dongles[id].queue);
	}
	pthread_mutex_destroy(&room->burnout_m);
	pthread_mutex_destroy(&room->print_m);
}

int	ft_out(t_programming_room *room, void *temp, int code)
{
	out_coders(room);
	out_dongles(room);
	trash(room->coders);
	trash(room->dongles);
	trash(room->inputs);
	trash(room);
	trash(temp);
	if (code)
		exit(code);
	fflush(stdout);
	return (code);
}
