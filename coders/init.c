/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:26:33 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/07 23:18:06 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
	i = 0;
	while (i < data->nb_coders)
	{
		pthread_mutex_init(&data->dongles[i].lock, NULL);
		pthread_cond_init(&data->dongles[i].cond, NULL);
		// init_heap(&data->dongles[i].queue);
		data->dongles[i].is_used = 0;
		data->dongles[i].available_at = 0;
		i++;
	}
	i = 0;
	while (i < data->nb_coders)
	{
		data->coders[i].id = i + 1;
		data->coders[i].left_dongle = &data->dongles[i];
		data->coders[i].compiles_done = 0;
		data->coders[i].right_dongle = &data->dongles[(i + 1)
			% data->nb_coders];
		data->coders[i].data = data;
		i++;
	}
	return (0);
}
