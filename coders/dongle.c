/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 22:38:08 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/13 23:50:23 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	get_timespec(long time, struct timespec *ts)
{
	ts->tv_sec = time / 1000;
	ts->tv_nsec = (time % 1000) * 1000000;
}

int	req_dongle(t_coder *coder, t_dongle *dongle)
{
	long			prio;
	struct timespec	ts;

	pthread_mutex_lock(&dongle->lock);
	prio = get_priority(coder);
	heap_push(&dongle->queue, coder->id, prio);
	while (dongle->is_used || get_time_ms() < dongle->available_at
		|| dongle->queue.heap[0].id != coder->id)
	{
		if (dongle->is_used || dongle->queue.heap[0].id != coder->id)
			pthread_cond_wait(&dongle->cond, &dongle->lock);
		else
		{
			get_timespec(dongle->available_at, &ts);
			pthread_cond_timedwait(&dongle->cond, &dongle->lock, &ts);
		}
		if (check_end(coder->data))
			return (pthread_mutex_unlock(&dongle->lock), 1);
	}
	heap_pop(&dongle->queue);
	dongle->is_used = 1;
	pthread_mutex_unlock(&dongle->lock);
	alt_print("has taken a dongle", coder);
	return (0);
}

void	rel_dongle(t_dongle *dongle, long cooldown)
{
	pthread_mutex_lock(&dongle->lock);
	dongle->is_used = 0;
	dongle->available_at = get_time_ms() + cooldown;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->lock);
}
