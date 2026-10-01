/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:10:53 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/01 13:35:05 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

enum policy{
	fifo = 1, edf = 2
};

typedef struct vars
{
	int	number_of_coders;
	time_t	time_to_burnout;
	time_t	time_to_compile;
	time_t	time_to_debug;
	time_t	time_to_refactor;
	int	number_of_compiles_required;
	time_t	dongle_cooldown;
	enum policy	scheduler;
}	t_vars;


typedef struct thread_state
{
	time_t		st_time;
	int			compilation_times;
	int			is_alive;
	int			coder_num;
	pthread_mutex_t	st_mutex;
	struct vars	*v;
}	t_tstate;

int	parser(int argc, char **argv, struct vars *v);
int	thread_init(struct vars *vars);
