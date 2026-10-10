/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:10:53 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/10 12:20:36 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum policy
{
	fifo = 1,
	edf = 2
}	t_policy;

typedef struct dongle_state
{
	int				state;
	pthread_mutex_t	dong_mutex;
	time_t			last_used;
}	t_dongle_s;

typedef struct vars
{
	int			number_of_coders;
	time_t		time_to_burnout;
	time_t		time_to_compile;
	time_t		time_to_debug;
	time_t		time_to_refactor;
	int			number_of_compiles_required;
	time_t		dongle_cooldown;
	t_policy	scheduler;
	time_t		st_run;
	int			*sim_state;
}	t_vars;

typedef struct dongle
{
	int				cooldown_time;
	t_dongle_s		**dongle_arr;
}	t_dongles;

typedef struct thread_state
{
	time_t			st_time;
	int				compilation_times;
	int				is_alive;
	int				coder_num;
	pthread_mutex_t	st_mutex;
	pthread_cond_t	cond;
	t_dongle_s		*lift_d;
	t_dongle_s		*right_d;
	t_vars			*v;
}	t_tstate;

typedef struct queue_el
{
	int	coder_num;
	int	coder_wight;
}	t_queue_el;

typedef struct queue
{
	t_queue_el	**qu;
	int			els_num;
	int			full_els_num;
}	t_queue;

typedef struct monitor_args
{
	t_tstate	**th_s;
	t_vars		*v;
	t_queue		*myqu;
	t_dongles	*dongle;
}	t_monitor_args;

typedef struct call_coder_res
{
	t_tstate	**th_s;
	pthread_t	*ths;
}	t_call_res;

int			parser(int argc, char **argv, t_vars *v);
time_t		get_start_time(void);

int			thread_init(t_vars *vars);

void		signal_it(t_queue *myqu, t_dongles *dongle,
				t_tstate **th_s);
void		unfinished_triger(t_monitor_args *m_args);

int			monitor_args_init(t_monitor_args **m_args,
				t_tstate ***th_s, t_vars *args);
int			is_live(t_tstate **th_s, int state, t_vars *v);
void		frees(t_monitor_args **m_args);
int			free_thread(t_tstate **th_s);
t_vars		*copy(t_vars *v);

int			creat_thread(t_vars *v, int num, t_tstate *th_s);
int			allocation(pthread_t **ths, t_tstate ***th_s, int coders);
t_dongles	*create_dongles(int size, t_vars v);
void		free_dongle(t_dongles *dongle, int size);

void		*coder(void *args);
void		is_burnout(struct timeval t, t_tstate *th_s, t_queue *myqu);

t_queue		*create_queue(int size);
int			calc_wight(t_tstate *th_s);
int			l_child(int index);
int			r_child(int index);
int			parent(int index);

int			push(t_tstate *th_s, t_policy policy, t_queue	*queue);
void		free_queue(t_queue *myqu);

int			swap_q_el(t_queue *myqu, int index, int smallest);
int			remove_it(t_queue *myqu, int coder);