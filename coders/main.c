/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:24:26 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/06 23:10:07 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse(int ac, char **av)
{
	int		i;
	int		j;
	long	val;

	if (ac != 9 || (ft_cmp(av[8], "fifo") != 0 && ft_cmp(av[8], "edf") != 0))
		return (1);
	i = 0;
	while (++i < 8)
	{
		if (ft_strlen(av[i]) > 11)
			return (1);
		j = -1;
		while (av[i][++j])
			if ((j == 0 && !(av[i][j] == '+' || (av[i][j] >= '0'
					&& av[i][j] <= '9'))) || (av[i][j] == '+'
					&& !av[i][j + 1]) || (j != 0 && (av[i][j] < '0'
						|| av[i][j] > '9')))
				return (1);
		val = ft_atoi(av[i]);
		if ((val < 0 || val > 2147483647))
			return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (parse(ac, av))
	{
		write(1, "codexion: invalid arguments\n", 29);
		return (1);
	}
	printf("ok");
	return (0);
}
