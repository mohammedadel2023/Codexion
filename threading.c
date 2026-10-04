/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/04 14:16:33 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*thread_monitor(void *args)
{
	int				it;
	struct timeval	t;
	t_tstate		**th_s;

	th_s = (struct thread_state **)args;
	while (is_live(th_s, 1))
	{
		it = 0;
		while (it < (th_s[0]->v->number_of_coders))
		{
			if (gettimeofday(&t, NULL) == 0 && th_s[it]->is_alive)
			{
				pthread_mutex_lock(&(th_s[it]->st_mutex));
				if (t.tv_sec - th_s[it]->st_time
					>= th_s[it]->v->time_to_burnout)
				{
					th_s[it]->is_alive = 0;
					printf("%i %i burned out\n", t.tv_sec, it);
				}
				else if (th_s[it]->compilation_times
					== th_s[it]->v->time_to_burnout)
					th_s[it]->is_alive = 0;
				pthread_mutex_unlock(&(th_s[it]->st_mutex));
			}
			it++;
		}
	}
	while (is_live(th_s, 0))
		usleep(1);
	printf("monitor thread stoped\n");
	free_thread(th_s);
	return (NULL);
}

int	thread_init(t_vars *vars)
{
	int				initiated_coder;
	pthread_t		*ths;
	pthread_t		monitor_th;
	t_tstate		**th_s;

	allocation(&ths, &th_s, vars->number_of_coders);
	initiated_coder = 0;
	while (initiated_coder < vars->number_of_coders)
	{
		creat_thread(vars, initiated_coder, th_s[initiated_coder]);
		if (!th_s[initiated_coder] || pthread_create(&ths[initiated_coder],
				NULL, &coder, (void *)th_s[initiated_coder]) != 0)
			return (3);
		initiated_coder++;
	}
	if (pthread_create(&monitor_th, NULL, &thread_monitor, (void *)th_s) != 0)
		return (5);
	initiated_coder = 0;
	while (initiated_coder < vars->number_of_coders)
	{
		pthread_join(ths[initiated_coder], NULL);
		initiated_coder++;
	}
	pthread_join(monitor_th, NULL);
	return (1);
}