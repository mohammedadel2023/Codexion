/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:10:53 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 14:39:31 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum policy{
	fifo = 1, edf = 2
} e_policy;

typedef struct vars
{
	int	number_of_coders;
	time_t	time_to_burnout;
	time_t	time_to_compile;
	time_t	time_to_debug;
	time_t	time_to_refactor;
	int	number_of_compiles_required;
	time_t	dongle_cooldown;
	//int		*stoped_coder;
	enum policy	scheduler;
}	t_vars;


typedef struct thread_state
{
	time_t		st_time;
	int			compilation_times;
	int			is_alive;
	int			coder_num;
	pthread_mutex_t	st_mutex;
	t_vars	*v;
}	t_tstate;

int	parser(int argc, char **argv, t_vars *v);
int	thread_init(t_vars *vars);
void    free_v(t_vars *v);
