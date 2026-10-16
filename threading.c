/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/16 17:03:34 by mkhashan         ###   ########.fr       */
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
		return (-1);
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
	if (sec_dong < coder)
	{
		pthread_mutex_lock(&dongle->dongle_arr[sec_dong]->dong_mutex);
		pthread_mutex_lock(&dongle->dongle_arr[coder]->dong_mutex);
	}
	else
	{
		pthread_mutex_lock(&dongle->dongle_arr[coder]->dong_mutex);
		pthread_mutex_lock(&dongle->dongle_arr[sec_dong]->dong_mutex);
	}
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
	pthread_mutex_lock(&th_s[coder]->st_mutex);
	th_s[coder]->is_queued = 0;
	th_s[coder]->is_alive = 1;
	pthread_cond_signal(&th_s[coder]->cond);
	pthread_mutex_unlock(&th_s[coder]->st_mutex);
}

void	signal_it(t_queue *myqu, t_dongles *dongle,
			t_tstate **th_s)
{
	int	qu_size;
	int	size;
	int	it;
	int	coder;

	it = 0;
	size = th_s[0]->v->number_of_coders;
	qu_size = myqu->els_num;
	while (it < qu_size)
	{
		coder = pull(myqu, dongle, *th_s[0]->v);
		if (coder > 0)
			lock_signal(th_s, dongle, coder - 1, size);
		it++;
	}
	reset_buffer(myqu, th_s);
}

void	unfinished_triger(t_monitor_args *m_args)
{
	int	it;

	it = 0;
	while (it < m_args->v->number_of_coders)
	{
		pthread_mutex_lock(&m_args->th_s[it]->st_mutex);
		if (m_args->th_s[it]->is_alive != -1)
		{
			m_args->th_s[it]->is_alive = 0;
			pthread_cond_signal(&m_args->th_s[it]->cond);
		}
		pthread_mutex_unlock(&m_args->th_s[it]->st_mutex);
		it++;
	}
}
