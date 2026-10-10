/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/10 11:58:39 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/10 12:13:32 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*thread_monitor(void *args)
{
	int				it;
	struct timeval	t;
	t_monitor_args	*m_args;

	m_args = (t_monitor_args *)args;
	while ((is_live(m_args->th_s, 1, m_args->v)
			|| is_live(m_args->th_s, 2, m_args->v))
		&& *m_args->v->sim_state)
	{
		it = 0;
		while (it < (m_args->th_s[0]->v->number_of_coders))
		{
			if (gettimeofday(&t, NULL) == 0 && m_args->th_s[it]->is_alive != 0)
			{
				is_burnout(t, m_args->th_s[it], m_args->myqu);
			}
			it++;
		}
		signal_it(m_args->myqu, m_args->dongle, m_args->th_s);
	}
	unfinished_triger(m_args);
	while (is_live(m_args->th_s, 0, m_args->v))
		usleep(1);
	return (NULL);
}

void	assign_dongles(t_tstate **th_s, t_dongles *dongle, t_vars v)
{
	int	it;

	it = 0;
	while (it < v.number_of_coders)
	{
		th_s[it]->lift_d = dongle->dongle_arr[it];
		th_s[it]->right_d = dongle->dongle_arr[(it + 1) % v.number_of_coders];
		it++;
	}
	free(dongle->dongle_arr);
	free(dongle);
}

t_call_res	*call_coders(t_vars *v)
{
	pthread_t	*ths;
	t_tstate	**th_s;
	int			initiated_coder;
	t_dongles	*dongle;
	t_call_res	*call_res;

	allocation(&ths, &th_s, v->number_of_coders);
	initiated_coder = 0;
	while (initiated_coder < v->number_of_coders)
	{
		creat_thread(v, initiated_coder + 1, th_s[initiated_coder]);
		if (!th_s[initiated_coder] || pthread_create(&ths[initiated_coder],
				NULL, &coder, (void *)th_s[initiated_coder]) != 0)
			return (NULL);
		initiated_coder++;
	}
	dongle = create_dongles(v->number_of_coders, *v);
	assign_dongles(th_s, dongle, *v);
	call_res = malloc(sizeof(t_call_res));
	if (!call_res)
		return (NULL);
	call_res->th_s = th_s;
	call_res->ths = ths;
	return (call_res);
}

int	thread_init(t_vars *vars)
{
	pthread_t		monitor_th;
	t_call_res		*call_res;
	t_monitor_args	*m_args;
	int				it;

	it = 0;
	call_res = call_coders(vars);
	if (!call_res)
		return (7);
	if (monitor_args_init(&m_args, &call_res->th_s, vars) == -1)
	{
		frees(&m_args);
		return (6);
	}
	if (pthread_create(&monitor_th, NULL, &thread_monitor, (void *)m_args) != 0)
		return (5);
	it = 0;
	pthread_join(monitor_th, NULL);
	while (it < vars->number_of_coders)
		pthread_join(call_res->ths[it++], NULL);
	frees(&m_args);
	return (1);
}
