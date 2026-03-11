/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:25:37 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/11 20:26:32 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RST "\033[0m"

# define BLACK "\033[30m"
# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define WHITE "\033[37m"

# define BBLACK "\033[1;30m"
# define BRED "\033[1;31m"
# define BGREEN "\033[1;32m"
# define BYELLOW "\033[1;33m"
# define BBLUE "\033[1;34m"
# define BMAGENTA "\033[1;35m"
# define BCYAN "\033[1;36m"
# define BWHITE "\033[1;37m"

# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"

typedef struct s_coder	t_coder;

typedef struct s_heap
{
	int					coder_ids[2];
	long				priorities[2];
	int					size;
}						t_heap;

typedef struct s_dongle
{
	pthread_mutex_t		lock;
	pthread_cond_t		cond;
	int					is_used;
	long				available_at;
	t_heap				queue;
}						t_dongle;

typedef struct s_data
{
	int					nb_coders;
	long				t_burnout;
	long				t_compile;
	long				t_debug;
	long				t_refactor;
	int					nb_compiles_req;
	long				cooldown;
	int					is_edf;

	long				start_time;
	int					sim_stop;

	pthread_mutex_t		print_lock;
	pthread_mutex_t		state_lock;

	t_dongle			*dongles;
	t_coder				*coders;
}						t_data;

struct					s_coder
{
	int					id;
	int					compiles_done;
	long				last_compile_start;
	t_data				*data;
	t_dongle			*first_dongle;
	t_dongle			*second_dongle;
	pthread_t			thread;
};

long					ft_atoi(const char *num);
int						ft_cmp(char *s1, char *s2);
int						ft_strlen(char *str);
int						init(t_data *data);
void					*routine(void *data);
long					get_time_ms(void);

#endif
