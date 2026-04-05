/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraghib <kraghib@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 21:25:37 by kraghib           #+#    #+#             */
/*   Updated: 2026/03/14 23:00:15 by kraghib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_coder	t_coder;

typedef struct s_hnode
{
	int					id;
	long				prio;
}						t_hnode;

typedef struct s_heap
{
	t_hnode				heap[2];
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
	long				compiles_done;
	long				last_compile_start;
	int					done;
	pthread_mutex_t		lock;
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
void					monitor(t_data *data);
long					get_priority(t_coder *c);
int						check_end(t_data *data);
void					alt_print(char *msg, t_coder *c);
void					alt_sleep(long sleep_time_ms, t_data *data);
int						req_dongle(t_coder *coder, t_dongle *dongle);
void					rel_dongle(t_dongle *dongle, long cooldown);
void					heap_push(t_heap *queue, int id, long prio);
void					heap_pop(t_heap *queue);
int						init_odd(t_data *data);
void					join_even_odd(t_data *data, int i);
int						init_even(t_data *data, int i);
void					clean(t_data *data);
void					join_even_odd(t_data *data, int i);

#endif
