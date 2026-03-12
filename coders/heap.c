/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 23:10:15 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/11 23:50:30 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
