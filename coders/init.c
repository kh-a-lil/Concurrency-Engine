/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:26:33 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/13 22:22:17 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_dongles(t_data *data, int i)
{
	pthread_mutex_init(&data->dongles[i].lock, NULL);
	pthread_cond_init(&data->dongles[i].cond, NULL);
	data->dongles[i].queue.size = 0;
	data->dongles[i].is_used = 0;
	data->dongles[i].available_at = 0;
}

void	init_coders(t_data *data, int i)
{
	data->coders[i].id = i + 1;
	data->coders[i].done = 0;
	data->coders[i].compiles_done = 0;
	data->coders[i].first_dongle = &data->dongles[i];
	data->coders[i].second_dongle = &data->dongles[(i + 1) % data->nb_coders];
	if (i % 2 != 0)
	{
		data->coders[i].second_dongle = &data->dongles[i];
		data->coders[i].first_dongle = &data->dongles[(i + 1)
			% data->nb_coders];
	}
	data->coders[i].data = data;
	pthread_mutex_init(&data->coders[i].lock, NULL);
}

int	init(t_data *data)
{
	int	i;

	data->coders = malloc(sizeof(t_coder) * data->nb_coders);
	if (!data->coders)
		return (1);
	data->dongles = malloc(sizeof(t_dongle) * data->nb_coders);
	if (!data->dongles)
	{
		free(data->coders);
		return (1);
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->state_lock, NULL);
	i = -1;
	while (++i < data->nb_coders)
		init_dongles(data, i);
	i = -1;
	while (++i < data->nb_coders)
		init_coders(data, i);
	return (0);
}

int	init_even(t_data *data, int i)
{
	while (++i < data->nb_coders)
	{
		if (i % 2 == 0)
		{
			data->coders[i].last_compile_start = data->start_time;
			if (pthread_create(&data->coders[i].thread, NULL, routine,
					&data->coders[i]))
			{
				pthread_mutex_lock(&data->state_lock);
				data->sim_stop = 1;
				pthread_mutex_unlock(&data->state_lock);
				while (--i >= 0)
				{
					if (i % 2 == 0)
						pthread_join(data->coders[i].thread, NULL);
				}
				fprintf(stderr, "error creating threads");
				clean(data);
				return (1);
			}
		}
	}
	return (0);
}

int	init_odd(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_coders)
	{
		if (i % 2 != 0)
		{
			data->coders[i].last_compile_start = data->start_time;
			if (pthread_create(&data->coders[i].thread, NULL, routine,
					&data->coders[i]))
			{
				pthread_mutex_lock(&data->state_lock);
				data->sim_stop = 1;
				pthread_mutex_unlock(&data->state_lock);
				join_even_odd(data, i);
				clean(data);
				fprintf(stderr, "error creating threads");
				return (1);
			}
		}
	}
	return (0);
}
