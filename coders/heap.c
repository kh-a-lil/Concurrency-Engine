/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:10:15 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/13 21:19:50 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_priority(t_coder *c)
{
	long			priority;
	struct timeval	tv;

	if (c->data->is_edf)
	{
		pthread_mutex_lock(&c->lock);
		priority = c->last_compile_start + c->data->t_burnout;
		pthread_mutex_unlock(&c->lock);
	}
	else
	{
		gettimeofday(&tv, NULL);
		priority = (tv.tv_sec * 1000000) + tv.tv_usec;
	}
	return (priority);
}

void	swap_nodes(t_hnode *heap)
{
	t_hnode	temp;

	temp = heap[0];
	heap[0] = heap[1];
	heap[1] = temp;
}

void	heap_push(t_heap *queue, int id, long prio)
{
	if (queue->size == 0)
	{
		queue->heap[0].id = id;
		queue->heap[0].prio = prio;
		queue->size = 1;
	}
	else if (queue->size == 1)
	{
		queue->heap[1].id = id;
		queue->heap[1].prio = prio;
		queue->size = 2;
		if (queue->heap[1].prio < queue->heap[0].prio)
			swap_nodes(queue->heap);
	}
}

void	heap_pop(t_heap *queue)
{
	if (queue->size == 1)
		queue->size = 0;
	else if (queue->size == 2)
	{
		swap_nodes(queue->heap);
		queue->size = 1;
	}
}
