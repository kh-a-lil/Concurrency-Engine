/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:25:37 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/06 21:53:06 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
}		t_data;

typedef struct s_dongle
{
}		t_dongle;

typedef struct s_coder
{
}		t_coder;

long	ft_atoi(const char *num);
int		ft_cmp(char *s1, char *s2);
int		ft_strlen(char *str);

#endif
