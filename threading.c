/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/10 12:06:57 by mkhashan         ###   ########.fr       */
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

	if (*v.sim_state == 0)
		return (0);
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

void	signal_it(t_queue *myqu, t_dongles *dongle,
		t_tstate **th_s)
{
	int	qu_size;
	int	size;
	int	it;
	int	proc;
	int	coder_idx;

	proc = 0;
	it = 0;
	size = th_s[0]->v->number_of_coders;
	qu_size = myqu->els_num;
	while (proc < qu_size && it < myqu->els_num)
	{
		coder_idx = myqu->qu[it]->coder_num - 1;
		if (is_dongle_free(coder_idx, dongle, *th_s[0]->v))
		{
			remove_it(myqu, coder_idx + 1);
			proc++;
			lock_signal(th_s, dongle, coder_idx, size);
		}
		else
			it++;
	}
}

void	unfinished_triger(t_monitor_args *m_args)
{
	int	it;

	it = 0;
	while (it < m_args->v->number_of_coders)
	{
		if (m_args->th_s[it]->is_alive != -1)
		{
			m_args->th_s[it]->is_alive = 0;
			pthread_mutex_lock(&m_args->th_s[it]->st_mutex);
			m_args->th_s[it]->is_alive = 0;
			pthread_cond_signal(&m_args->th_s[it]->cond);
			pthread_mutex_unlock(&m_args->th_s[it]->st_mutex);
		}
		it++;
	}
}
