/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:25:37 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/06 23:52:43 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder t_coder;

typedef struct s_heap
{
	int				coder_ids[250];
	long			priorities[250];
	int				size;
}					t_heap;

typedef struct s_dongle
{
	pthread_mutex_t	lock;
	pthread_cond_t	cond;
	int				is_used;
	long			available_at;
	t_heap			queue;
}					t_dongle;

typedef struct s_data
{
	int				nb_coders;
	long			t_burnout;
	long			t_compile;
	long			t_debug;
	long			t_refactor;
	int				nb_compiles_req;
	long			cooldown;
	int				is_edf;

	long			start_time;
	int				sim_stop;

	pthread_mutex_t	print_lock;
	pthread_mutex_t	state_lock;

	t_dongle		*dongles;
	t_coder			*coders;
}					t_data;

struct s_coder
{
	int				id;
	int				compiles_done;
	long			last_compile_start;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_data			*data;
	pthread_t		thread;
};

long				ft_atoi(const char *num);
int					ft_cmp(char *s1, char *s2);
int					ft_strlen(char *str);

#endif
