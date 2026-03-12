/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:38:08 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/12 00:04:02 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	req_dongle(t_coder *coder, t_dongle *dongle)
{
	long	prio;

	pthread_mutex_lock(&dongle->lock);
	prio = get_priority(coder);
	heap_push(&dongle->queue, coder->id, prio);
	while (dongle->is_used || get_time_ms() < dongle->available_at
		|| dongle->queue.heap[0].id != coder->id)
		pthread_cond_wait(&dongle->cond, &dongle->lock);
	heap_pop(&dongle->queue);
	dongle->is_used = 1;
	pthread_mutex_unlock(&dongle->lock);
	alt_print(" has taken a dongle", coder);
}

void	rel_dongle(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_used = 0;
	dongle->available_at = get_time_ms() - cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}
