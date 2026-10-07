/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:16:35 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/07 12:40:11 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_live(t_tstate **th_s, int state, t_vars v)
{
	int	it;

	it = 0;
	while (it < v.number_of_coders)
	{
		fprintf(stderr, "the coder [%i] is the problem\n", th_s[it]->coder_num);
		pthread_mutex_lock(&th_s[it]->st_mutex);
		fprintf(stderr, "the coder [%i] \n", th_s[it]->is_alive == state);
		fprintf(stderr, "the coder state [%i] \n", th_s[it]->is_alive);
		if (th_s[it]->is_alive == state)
		{
			//fprintf(stderr, "the coder [%i] is the problem\n", th_s[it]->coder_num);
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

int	monitor_args_init(t_monitor_args **m_args, t_tstate ***th_s, t_vars args)
{
	t_queue	*myqu;

	*m_args = malloc(sizeof(t_monitor_args));
	if (!m_args)
		return (-1);
	(*m_args)->th_s = *th_s;
	(*m_args)->v = args;
	(*m_args)->myqu = create_queue(args.number_of_coders);
	(*m_args)->dongle = create_dongles(args.number_of_coders, args);
	return (0);
}

void	frees(t_monitor_args **m_args)
{
	free_thread((*m_args)->th_s);
	free_queue((*m_args)->myqu);
	free_dongle((*m_args)->dongle, (*m_args)->v.number_of_coders);
	free(*m_args);
}
