/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 21:21:36 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/14 00:11:29 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	alt_print(char *msg, t_coder *c)
{
	pthread_mutex_lock(&c->data->print_lock);
	if (!check_end(c->data))
		printf("%ld %d %s\n", get_time_ms() - c->data->start_time, c->id, msg);
	pthread_mutex_unlock(&c->data->print_lock);
}

void	alt_sleep(long sleep_time_ms, t_data *data)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < sleep_time_ms)
	{
		if (check_end(data))
			break ;
		usleep(200);
	}
}

void	join_even_odd(t_data *data, int i)
{
	while (--i >= 0)
		if (i % 2 != 0)
			pthread_join(data->coders[i].thread, NULL);
	i = data->nb_coders;
	while (--i >= 0)
		if (i % 2 == 0)
			pthread_join(data->coders[i].thread, NULL);
}
