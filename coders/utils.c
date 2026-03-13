/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:38:07 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/13 21:20:54 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	ft_atoi(const char *num)
{
	long	sign;
	long	result;

	sign = 1;
	result = 0;
	while ((*num && (*num < 14 && *num > 8)) || *num == 32)
		num++;
	if (*num == '+' || *num == '-')
	{
		if (*num == '-')
			sign *= -1;
		num++;
	}
	while (*num >= '0' && *num <= '9')
	{
		result = result * 10 + (*num - '0');
		num++;
	}
	return (result * sign);
}

int	ft_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

long	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	check_end(t_data *data)
{
	int	stop;

	pthread_mutex_lock(&data->state_lock);
	stop = data->sim_stop;
	pthread_mutex_unlock(&data->state_lock);
	return (stop);
}
