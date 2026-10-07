/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/07 17:51:06 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_dongle_free(int coder, t_dongles dongle, int size)
{
	if ((dongle.dongle_arr[coder]->state)
		&& dongle.dongle_arr[coder + 1 % size]->state)
		return (1);
	return (0);
}

void	signal(t_queue *myqu, t_dongles *dongle, t_tstate **th_s)
{
	int	coder;
	int	size;
	int	it;

	it = 1;
	size = th_s[0]->v->number_of_coders;
	coder = top(myqu);
	if (is_dongle_free(coder, *dongle,
		size));
	{
		dongle->dongle_arr[coder]->state = 0;
		dongle->dongle_arr[(coder + 1) % size]->state = 0;
		pull(myqu);
		pthread_cond_signal(&th_s[coder]->cond);
		//return;
	}
	while (it < myqu->els_num)
	{
		coder = myqu->qu[it]->coder_num;
		if (is_dongle_free(coder, *dongle, size))
		{
			dongle->dongle_arr[coder]->state = 0;
			dongle->dongle_arr[(coder + 1) % size]->state = 0;
			remove_it(myqu, coder);
			pthread_cond_signal(&th_s[coder]->cond);
			//return;
		}
	}
	
}

void	*thread_monitor(void *args)
{
	int				it;
	struct timeval	t;
	t_monitor_args	*m_args;

	m_args = (t_monitor_args *)args;
	printf("start monitor thread\n");
	while (is_live(m_args->th_s, 1, m_args->v)
			|| is_live(m_args->th_s, 2, m_args->v))
	{
		it = 0;
		while (it < (m_args->th_s[0]->v->number_of_coders))
		{
			if (gettimeofday(&t, NULL) == 0 && m_args->th_s[it]->is_alive == 1)
				is_burnout(t.tv_sec, m_args->th_s[it], m_args->myqu);
			it++;
		}
		signal(m_args->myqu, m_args->dongle, m_args->th_s);
	}
	while (is_live(m_args->th_s, 0, m_args->v))
		usleep(1);
	printf("monitor thread stoped\n");
	frees(&m_args);
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
}

t_tstate	**call_coders(t_vars v)
{
	pthread_t	*ths;
	t_tstate	**th_s;
	int			initiated_coder;
	t_dongles	*dongle;

	allocation(&ths, &th_s, v.number_of_coders);
	initiated_coder = 0;
	while (initiated_coder < v.number_of_coders)
	{
		creat_thread(&v, initiated_coder + 1, th_s[initiated_coder]);
		if (!th_s[initiated_coder] || pthread_create(&ths[initiated_coder],
				NULL, &coder, (void *)th_s[initiated_coder]) != 0)
			return (NULL);
		initiated_coder++;
	}
	dongle = create_dongles(v.number_of_coders, v);
	assign_dongles(th_s, dongle, v);
	initiated_coder = 0;
	while (initiated_coder < v.number_of_coders)
		pthread_join(ths[initiated_coder++], NULL);
	free(ths);
	free(dongle->dongle_arr);
	free(dongle);
	return (th_s);
}

int	thread_init(t_vars *vars)
{
	pthread_t		monitor_th;
	t_tstate		**th_s;
	t_monitor_args	*m_args;

	th_s = call_coders(*vars);
	if (monitor_args_init(&m_args, &th_s, *vars) == -1)
	{
		frees(&m_args);
		return (6);
	}
	if (pthread_create(&monitor_th, NULL, &thread_monitor, (void *)m_args) != 0)
		return (5);
	pthread_join(monitor_th, NULL);
	return (1);
}
