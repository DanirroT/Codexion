/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_man.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:36:53 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/15 22:15:35 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	perform_edf(t_list **queue_head, t_coder *coder)
{
	t_list	**searching_in;
	t_list	*temp;
	t_coder	*temp_coder;
	t_coder	*first;
	t_coder	*second;

	searching_in = queue_head;
	while (*searching_in)
	{
		temp_coder = (*searching_in)->content;
		if (temp_coder->id > coder->id)
		{
			first = temp_coder;
			second = coder;
		}
		else
		{
			first = coder;
			second = temp_coder;
		}
		pthread_mutex_lock(&first->compiling_m);
		pthread_mutex_lock(&second->compiling_m);
		// fprintf(stderr, "to add: %i %lli looking at: %i %lli\n",
		// 	coder->id, coder->last_ct,
		// 	temp_coder->id, temp_coder->last_ct);
		// printf("searching %lli > %lli", temp_coder->last_ct,
		// 	coder->last_ct);
		if (coder->last_ct + coder->room->inputs->time_to_burnout
			< temp_coder->last_ct
			+ coder->room->inputs->time_to_burnout)
		{
			fprintf(stderr, "\t\tFOUND!\n");
			temp = (*searching_in);
			(*searching_in) = ft_lstnew(coder);
			(*searching_in)->next = temp;
			pthread_mutex_unlock(&second->compiling_m);
			pthread_mutex_unlock(&first->compiling_m);
			return ;
		}
		searching_in = &(*searching_in)->next;
		pthread_mutex_unlock(&second->compiling_m);
		pthread_mutex_unlock(&first->compiling_m);
	}
	(*searching_in) = ft_lstnew(coder);
}

void	add_d_queue(t_dongle *dongle, t_coder *coder)
{
	t_list	**queue;

	queue = &dongle->queue;
	pthread_mutex_lock(&dongle->state_m);
	if (!ft_lstsize(*queue))
		*queue = ft_lstnew(coder);
	else
	{
		if (coder->room->inputs->scheduler == FIFO)
			ft_lstadd_back(queue, ft_lstnew(coder));
		if (coder->room->inputs->scheduler == EDF)
			perform_edf(queue, coder);
	}
	pthread_mutex_unlock(&dongle->state_m);
}

void	remove_from_queue(t_dongle *dongle, int id)
{
	t_list	*temp;
	t_list	**queue;

	queue = &dongle->queue;
	if (!queue || !*queue)
		return ;
	temp = (*queue);
	(*queue) = temp->next;
	print_queue(dongle->queue, dongle->id, "Out");
	dongle->state = HELD;
	print_event(dongle->room, id, "has taken a dongle");
	fprintf(stderr, "\tBroadcast %p (%p)\n",
		&dongle->take, &dongle->state_m);
	free(temp);
}

void	print_queue(t_list *queue, int d_id, char *s)
{
	t_coder	*coder;
	int		i;

	i = 1;
	fprintf(stderr, "%s Printing Queue of D%i:", s, d_id);
	while (queue)
	{
		coder = (t_coder *)queue->content;
		fprintf(stderr, "\t%i: %i", i, coder->id);
		i++;
		queue = queue->next;
	}
	fprintf(stderr, "\n");
}
