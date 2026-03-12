/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 01:57:02 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/11 22:28:09 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_priority(t_coder *c)
{
	long			priority;
	struct timeval	tv;

	if (c->data->is_edf)
	{
		// EDF: Priority is the exact millisecond they will die
		pthread_mutex_lock(&c->data->state_lock);
		priority = c->last_compile_start + c->data->t_burnout;
		pthread_mutex_unlock(&c->data->state_lock);
	}
	else
	{
		// FIFO: Priority is the exact microsecond they arrived
		gettimeofday(&tv, NULL);
		priority = (tv.tv_sec * 1000000) + tv.tv_usec;
	}
	return (priority);
}

void	monitor(t_data *data)
{
}
