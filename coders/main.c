/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:24:26 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/06 22:16:24 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	parse(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 9 || (ft_cmp(av[8], "fifo") != 0 && ft_cmp(av[8], "edf") != 0))
		return (1);
	i = 1;
	while (i < 8)
	{
		if (ft_strlen(av[i]) > 11)
			return (1);
		j = 0;
		while (av[i][j])
		{
			if ((j == 0 && !(av[i][j] == '+'
				|| (av[i][j] >= '0' && av[i][j] <= '9')))
				|| ((av[i][j] == '+') && !(av[i][j + 1])))
				return (1);
			if (j != 0 && (av[i][j] < '0' || av[i][j] > '9'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	if (parse(ac, av))
	{
		write(1, "err", 3);
		return (1);
	}
	printf("ok");
	return (0);
}
