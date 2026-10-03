/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:10:53 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 19:24:29 by mkhashan         ###   ########.fr       */
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
}	t_vars;

typedef struct thread_state
{
	time_t			st_time;
	int				compilation_times;
	int				is_alive;
	int				coder_num;
	pthread_mutex_t	st_mutex;
	t_vars			*v;
}	t_tstate;

typedef struct queue_el
{
	int	el_num;
	int	el_wight;
}	t_queue_el;

typedef struct montiort_args
{
	t_tstate	**th_s;
	t_vars		v;
	t_queue_el	*queue;
}	t_monitor_args;

int		parser(int argc, char **argv, t_vars *v);
int		thread_init(t_vars *vars);
t_vars	*copy(t_vars *v);

int	creat_thread(t_vars *v, int num, t_tstate *th_s);
int	allocation(pthread_t **ths, t_tstate ***th_s, int coders);

void	*coder(void *args);
