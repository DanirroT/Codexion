/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_man.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmota-ri <dmota-ri@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 19:36:53 by dmota-ri          #+#    #+#             */
/*   Updated: 2026/07/20 14:07:06 by dmota-ri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	has_higher_priority(t_coder *new, t_coder *current)
{
	t_coder	*first;
	t_coder	*second;
	int		result;

	if (new->id < current->id)
	{
		first = new;
		second = current;
	}
	else
	{
		first = current;
		second = new;
	}
	pthread_mutex_lock(&first->compiling_m);
	pthread_mutex_lock(&second->compiling_m);
	result = (new->last_ct < current->last_ct);
	pthread_mutex_unlock(&second->compiling_m);
	pthread_mutex_unlock(&first->compiling_m);
	return (result);
}

static void	perform_edf(t_list **queue, t_coder *coder)
{
	t_list	*temp;

	while (*queue)
	{
		if (has_higher_priority(coder, (*queue)->content))
		{
			temp = (*queue);
			(*queue) = ft_lstnew(coder);
			(*queue)->next = temp;
			return ;
		}
		queue = &(*queue)->next;
	}
	(*queue) = ft_lstnew(coder);
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

void	remove_from_queues(t_coder *coder)
{
	t_list	*temp;
	t_list	**queue;

	queue = &coder->dongle_l->queue;
	temp = (*queue);
	(*queue) = temp->next;
	print_queue(coder->dongle_l->queue, coder->dongle_l->id, "Out");
	coder->dongle_l->state = HELD;
	print_event(coder->room, coder->id, "has taken a dongle");
	fprintf(stderr, "\tBroadcast Take D%i %p (%p)\n",
		coder->dongle_l->id, &coder->dongle_l->take, &coder->dongle_l->state_m);
	free(temp);

	queue = &coder->dongle_r->queue;
	temp = (*queue);
	(*queue) = temp->next;
	print_queue(coder->dongle_r->queue, coder->dongle_r->id, "Out");
	coder->dongle_r->state = HELD;
	print_event(coder->room, coder->id, "has taken a dongle");
	fprintf(stderr, "\tBroadcast Take D%i %p (%p)\n",
		coder->dongle_r->id, &coder->dongle_r->take, &coder->dongle_r->state_m);

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
