/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 01:57:02 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/13 23:20:59 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	monitor_loop(t_data *data, int i, int *all_finished)
{
	int	j;

	pthread_mutex_lock(&data->state_lock);
	pthread_mutex_lock(&data->coders[i].lock);
	if (data->coders[i].done == 0 && get_time_ms()
		- data->coders[i].last_compile_start > data->t_burnout)
	{
		data->sim_stop = 1;
		pthread_mutex_unlock(&data->state_lock);
		j = -1;
		pthread_mutex_unlock(&data->coders[i].lock);
		while (++j < data->nb_coders){
			pthread_mutex_lock(&data->dongles[j].lock);
			pthread_cond_broadcast(&data->dongles[j].cond);
			pthread_mutex_unlock(&data->dongles[j].lock);
		}
		pthread_mutex_lock(&data->print_lock);
		printf("%ld %d %s\n", get_time_ms() - data->start_time,
			data->coders[i].id, "burned out");
		pthread_mutex_unlock(&data->print_lock);
		return (1);
	}
	if (data->coders[i].done == 0)
		*all_finished = 0;
	pthread_mutex_unlock(&data->state_lock);
	pthread_mutex_unlock(&data->coders[i].lock);
	return (0);
}

void	monitor(t_data *data)
{
	int	i;
	int	all_finished;

	while (1)
	{
		all_finished = 1;
		i = -1;
		while (++i < data->nb_coders)
			if (monitor_loop(data, i, &all_finished))
				return ;
		if (all_finished)
		{
			pthread_mutex_lock(&data->state_lock);
			data->sim_stop = 1;
			pthread_mutex_unlock(&data->state_lock);
			return ;
		}
		usleep(500);
	}
}
