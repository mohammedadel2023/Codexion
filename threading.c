/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 17:01:28 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*thread_monitor(void *args)
{
	int				it;
	struct timeval	t;
	t_monitor_args	*m_args;

	m_args = (t_monitor_args *)args;
	while (is_live(m_args->th_s, 1))
	{
		it = 0;
		while (it < (m_args->th_s[0]->v->number_of_coders))
		{
			if (gettimeofday(&t, NULL) == 0 && m_args->th_s[0]->is_alive)
				is_burnout(t.tv_sec, m_args->th_s[0]);
			it++;
		}
	}
	while (is_live(m_args->th_s, 0))
		usleep(1);
	printf("monitor thread stoped\n");
	free_thread(m_args->th_s);
	free(m_args);
	return (NULL);
}

int	thread_init(t_vars *vars)
{
	int				initiated_coder;
	pthread_t		*ths;
	pthread_t		monitor_th;
	t_tstate		**th_s;
	t_monitor_args	*m_args;

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
	if (monitor_args_init(&m_args, &th_s, *vars) == -1)
		return (6);
	if (pthread_create(&monitor_th, NULL, &thread_monitor, (void *)m_args) != 0)
		return (5);
	initiated_coder = 0;
	while (initiated_coder < vars->number_of_coders)
	{
		pthread_join(ths[initiated_coder], NULL);
		initiated_coder++;
	}
	free(ths);
	pthread_join(monitor_th, NULL);
	return (1);
}
