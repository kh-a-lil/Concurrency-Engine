/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:53:03 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/14 00:14:18 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	looper(t_coder *c)
{
	if (req_dongle(c, c->first_dongle) || req_dongle(c, c->second_dongle))
		return (1);
	pthread_mutex_lock(&c->lock);
	c->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&c->lock);
	c->compiles_done++;
	alt_print("is compiling", c);
	alt_sleep(c->data->t_compile, c->data);
	rel_dongle(c->first_dongle, c->data->cooldown);
	rel_dongle(c->second_dongle, c->data->cooldown);
	if (c->compiles_done == c->data->nb_compiles_req)
	{
		pthread_mutex_lock(&c->lock);
		c->done = 1;
		pthread_mutex_unlock(&c->lock);
		return (1);
	}
	alt_print("is debugging", c);
	alt_sleep(c->data->t_debug, c->data);
	alt_print("is refactoring", c);
	alt_sleep(c->data->t_refactor, c->data);
	return (0);
}

void	*routine(void *arg)
{
	t_coder	*c;

	c = (t_coder *)arg;
	if (c->data->nb_coders == 1)
	{
		req_dongle(c, c->first_dongle);
		while (!check_end(c->data))
			usleep(500);
		rel_dongle(c->first_dongle, c->data->cooldown);
		return (NULL);
	}
	if (c->compiles_done == c->data->nb_compiles_req)
	{
		pthread_mutex_lock(&c->lock);
		c->done = 1;
		pthread_mutex_unlock(&c->lock);
		return (NULL);
	}
	while (!check_end(c->data))
		if (looper(c))
			break ;
	return (NULL);
}
