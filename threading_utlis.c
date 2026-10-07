/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading_utlis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:01:39 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/07 15:25:15 by mkhashan         ###   ########.fr       */
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
	th_s->st_time = (time->tv_sec * 1000) + time->tv_usec / 1000 - v->st_run;
	th_s->compilation_times = 0;
	th_s->is_alive = 1;
	th_s->coder_num = num;
	if (pthread_cond_init(&(th_s->cond), NULL) != 0)
		return (-2);
	if (pthread_mutex_init(&(th_s->st_mutex), NULL) != 0)
		return (-3);
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

int	create_dongle_s(int size, t_dongle_s **dongle_s)
{
	int	it;

	it = 0;
	while (it < size)
	{
		dongle_s[it] = malloc(sizeof(t_dongle_s));
		if (!dongle_s[it])
		{
			while (it > 0)
				free(dongle_s[--it]);
			return (-3);
		}
		pthread_mutex_init(&(dongle_s[it]->dong_mutex), NULL);
		dongle_s[it]->state = 1;
		it++;
	}
	return (0);
}

t_dongles	*create_dongles(int size, t_vars v)
{
	t_dongles	*dongle;
	t_dongle_s	**dongle_s;

	if (size <= 0)
		return (NULL);
	dongle = malloc(sizeof(t_dongles));
	if (!dongle)
		return (NULL);
	dongle->cooldown_time = v.dongle_cooldown;
	dongle->dongle_arr = NULL;
	dongle_s = malloc(sizeof(t_dongle_s *) * size);
	if (!dongle_s)
	{
		free(dongle);
		return (NULL);
	}
	if (create_dongle_s(size, dongle_s) != 0)
	{
		free(dongle_s);
		free(dongle);
		return (NULL);
	}
	dongle->dongle_arr = dongle_s;
	return (dongle);
}

void	free_dongle(t_dongles *dongle, int size)
{
	int	it;

	it = 0;
	while (it < size)
	{
		pthread_mutex_destroy(&(dongle->dongle_arr[it]->dong_mutex));
		free(dongle->dongle_arr[it]);
		it++;
	}
	free(dongle->dongle_arr);
	free(dongle);
}
