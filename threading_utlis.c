/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_utlis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:01:39 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 15:51:30 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	creat_thread(t_vars *v, int num, t_tstate *th_s)
{
	struct timeval	*time;

	time = malloc(sizeof(struct timeval));
	if (!time)
		return (-1);
	if (gettimeofday(time, NULL))
		return (-1);
	th_s->v = copy(v);
	th_s->st_time = time->tv_sec;
	th_s->compilation_times = 0;
	th_s->is_alive = 1;
	th_s->coder_num = num;
	if (pthread_mutex_init(&(th_s->st_mutex), NULL) != 0)
		return (-2);
	free(time);
	return (0);
}

int	allocation(pthread_t **ths, t_tstate ***th_s, int coders)
{
	int	it;

	it = 0;
	*ths = malloc(sizeof(pthread_t) * coders);
	if (!ths)
		return (-1);
	*th_s = malloc(sizeof(t_tstate *) * coders);
	if (!th_s)
	{
		free(ths);
		return (-2);
	}
	while (coders > it)
	{
		(*th_s)[it++] = malloc(sizeof(t_tstate));
		if (!(*th_s)[it - 1])
		{
			free(*ths);
			while (--it != 0)
				free((*th_s)[it]);
			free(*th_s);
			return (-3);
		}
	}
	return (0);
}
