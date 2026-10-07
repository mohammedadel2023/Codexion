/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:16:35 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/07 15:24:45 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_live(t_tstate **th_s, int state, t_vars v)
{
	int	it;

	it = 0;
	while (it < v.number_of_coders)
	{

		pthread_mutex_lock(&th_s[it]->st_mutex);
		if (th_s[it]->is_alive == state)
		{
			pthread_mutex_unlock(&th_s[it]->st_mutex);
			return (1);
		}
		pthread_mutex_unlock(&th_s[it]->st_mutex);
		it++;
	}
	return (0);
}

t_vars	*copy(t_vars *v)
{
	t_vars	*new_v;

	new_v = malloc(sizeof(struct vars));
	*new_v = *v;
	return (new_v);
}

int	free_thread(t_tstate **th_s)
{
	int	it;

	if (!th_s)
		return (0);
	it = th_s[0]->v->number_of_coders;
	while (0 <= it - 1)
	{
		pthread_mutex_destroy(&th_s[it - 1]->st_mutex);
		pthread_cond_destroy(&(th_s[it - 1]->cond));
		free(th_s[it - 1]->v);
		free(th_s[it - 1]);
		it--;
	}
	free(th_s);
	return (1);
}

t_dongles	*sub_create_dongle(t_tstate **th_s, t_vars v)
{
	t_dongles	*dongle;
	t_dongle_s	**dongle_s;
	int			it;

	it = 0;
	dongle = malloc(sizeof(t_dongles));
	if (!dongle)
		return (NULL);
	dongle_s = malloc(sizeof(t_dongle_s *) * (v.number_of_coders + 1));
	if (!dongle_s)
	{
		free(dongle);
		return (NULL);
	}
	while (it < v.number_of_coders)
	{
		dongle_s[it] = th_s[it]->lift_d;
		it++;
	}
	dongle->dongle_arr = dongle_s;
	dongle->cooldown_time = v.dongle_cooldown;
	return (dongle);
}

int	monitor_args_init(t_monitor_args **m_args, t_tstate ***th_s, t_vars args)
{
	t_queue	*myqu;

	*m_args = malloc(sizeof(t_monitor_args));
	if (!m_args)
		return (-1);
	(*m_args)->th_s = *th_s;
	(*m_args)->v = args;
	(*m_args)->myqu = create_queue(args.number_of_coders);
	(*m_args)->dongle = sub_create_dongle(*th_s, args);
	if (!(*m_args)->dongle)
		return (-1);
	return (0);
}

void	frees(t_monitor_args **m_args)
{
	free_queue((*m_args)->myqu);
	free_dongle((*m_args)->dongle, (*m_args)->v.number_of_coders);
	free_thread((*m_args)->th_s);
	free(*m_args);
}
