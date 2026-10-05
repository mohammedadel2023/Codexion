/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:16:35 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 15:56:18 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_live(t_tstate **th_s, int state)
{
	int	it;

	it = 0;
	while (it < th_s[0]->v->number_of_coders)
	{
		if (th_s[it]->is_alive == state)
			return (1);
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
		free(th_s[it - 1]->v);
		free(th_s[it - 1]);
		it--;
	}
	free(th_s);
	return (1);
}

int	monitor_args_init(t_monitor_args **m_args, t_tstate ***th_s, t_vars args)
{
	*m_args = malloc(sizeof(t_monitor_args));
	if (!m_args)
		return (-1);
	(*m_args)->th_s = *th_s;
	(*m_args)->v = args;
	return (0);
}