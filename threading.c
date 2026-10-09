/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/09 14:16:47 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_free_dong(t_dongles *dongle, int coder, t_vars v)
{
	struct timeval	t;
	time_t			time;
	time_t			cooldown;
	int				size;
	int				sec_dong;

	cooldown = v.dongle_cooldown;
	size = v.number_of_coders;
	sec_dong = (coder + 1) % size;
	if (gettimeofday(&t, NULL) != 0)
		return (0);
	time = (t.tv_sec * 1000) + (t.tv_usec / 1000) - v.st_run;
	if (((time - dongle->dongle_arr[coder]->last_used) < cooldown)
		|| ((time - dongle->dongle_arr[sec_dong]->last_used) < cooldown))
		return (0);
	if ((dongle->dongle_arr[coder]->state != 1)
		|| dongle->dongle_arr[sec_dong]->state != 1)
		return (0);
	return (1);
}

int	is_dongle_free(int coder, t_dongles *dongle, t_vars v)
{
	int	sec_dong;
	int	size;
	int	cooldown;

	cooldown = v.dongle_cooldown;
	size = v.number_of_coders;
	sec_dong = (coder + 1) % size;
	pthread_mutex_lock(&dongle->dongle_arr[coder]->dong_mutex);
	pthread_mutex_lock(&dongle->dongle_arr[sec_dong]->dong_mutex);
	if (is_free_dong(dongle, coder, v) == 0)
	{
		pthread_mutex_unlock(&dongle->dongle_arr[coder]->dong_mutex);
		pthread_mutex_unlock(&dongle->dongle_arr[sec_dong]->dong_mutex);
		return (0);
	}
	return (1);
}

void	lock_signal(t_tstate **th_s, t_dongles *dongle, int coder, int size)
{
	dongle->dongle_arr[coder]->state = 0;
	dongle->dongle_arr[(coder + 1) % size]->state = 0;
	pthread_mutex_unlock(&dongle->dongle_arr[coder]->dong_mutex);
	pthread_mutex_unlock(&dongle->dongle_arr[(coder + 1) % size]->dong_mutex);
	pthread_cond_signal(&th_s[coder]->cond);
}

void	signal_it(t_queue *myqu, t_dongles *dongle, t_tstate **th_s, int cooldown)
{
	int	qu_size;
	int	size;
	int	it;
	int	proc;

	proc = 0;
	it = 0;
	size = th_s[0]->v->number_of_coders;
	qu_size = myqu->els_num;
	while (proc < qu_size)
	{
		if (is_dongle_free(myqu->qu[it]->coder_num - 1, dongle, *th_s[it]->v))
		{
			remove_it(myqu, myqu->qu[it]->coder_num);
			proc++;
			lock_signal(th_s, dongle, myqu->qu[it]->coder_num - 1, size);
		}
		else
			it++;
	}
}

void	*thread_monitor(void *args)
{
	int				it;
	struct timeval	t;
	t_monitor_args	*m_args;

	m_args = (t_monitor_args *)args;
	while ((is_live(m_args->th_s, 1, m_args->v)
			|| is_live(m_args->th_s, 2, m_args->v))
		&& m_args->v.sim_state)
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
		signal_it(m_args->myqu, m_args->dongle, m_args->th_s,
			m_args->v.dongle_cooldown);
	}
	while (is_live(m_args->th_s, 0, m_args->v))
		usleep(1);
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
	free(dongle->dongle_arr);
	free(dongle);
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
	if (monitor_args_init(&m_args, &call_res->th_s, *vars) == -1)
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
	return (1);
}
