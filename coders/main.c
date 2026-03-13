/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:24:26 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/13 21:41:35 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	error(char *str)
{
	fprintf(stderr, "codexion: %s\n", str);
	return (1);
}

int	parse(int ac, char **av)
{
	int		i;
	int		j;
	long	val;

	if (ac != 9 || (ft_cmp(av[8], "fifo") != 0 && ft_cmp(av[8], "edf") != 0))
		return (error("scheduler must be fifo or edf"));
	i = 0;
	while (++i < 8)
	{
		if (ft_strlen(av[i]) > 11)
			return (error("input number out of range"));
		j = -1;
		while (av[i][++j])
			if ((j == 0 && !(av[i][j] == '+' || (av[i][j] >= '0'
					&& av[i][j] <= '9'))) || (av[i][j] == '+'
					&& !av[i][j + 1]) || (j != 0 && (av[i][j] < '0'
						|| av[i][j] > '9')))
				return (error("invalid input number"));
		val = ft_atoi(av[i]);
		if ((val < 0 || val > 2147483647))
			return (error("input number out of range"));
	}
	return (0);
}

int	fill_data(char **av, t_data *data)
{
	data->nb_coders = ft_atoi(av[0]);
	data->t_burnout = ft_atoi(av[1]);
	data->t_compile = ft_atoi(av[2]);
	data->t_debug = ft_atoi(av[3]);
	data->t_refactor = ft_atoi(av[4]);
	data->nb_compiles_req = ft_atoi(av[5]);
	data->cooldown = ft_atoi(av[6]);
	data->is_edf = 0;
	if (ft_cmp(av[7], "fifo"))
		data->is_edf = 1;
	data->start_time = 0;
	data->sim_stop = 0;
	if (data->nb_coders < 1)
		return (error("invalid number_of_coders"));
	if (data->t_burnout < 60 || data->t_compile < 60 || data->t_debug < 60
		|| data->t_refactor < 60)
		return (error("time values must be > 60"));
	return (0);
}

void	clean(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = -1;
	if (data->dongles)
	{
		while (++i < data->nb_coders)
		{
			pthread_mutex_destroy(&data->dongles[i].lock);
			pthread_cond_destroy(&data->dongles[i].cond);
		}
		free(data->dongles);
	}
	i = -1;
	if (data->coders)
	{
		while (++i < data->nb_coders)
			pthread_mutex_destroy(&data->coders[i].lock);
		free(data->coders);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->state_lock);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	if (parse(ac, av))
		return (1);
	if (fill_data(av + 1, &data))
		return (1);
	init(&data);
	data.start_time = get_time_ms();
	if (init_even(&data, -1))
		return (1);
	if (init_odd(&data))
		return (1);
	monitor(&data);
	i = -1;
	while (++i < data.nb_coders)
		pthread_join(data.coders[i].thread, NULL);
	clean(&data);
	return (0);
}
