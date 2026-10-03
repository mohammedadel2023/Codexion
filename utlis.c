/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 13:01:39 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 18:42:18 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	free_v(t_vars *v)
{
	free(v);
}

void	*creat_thread(t_vars *v, int num)
{
	struct timeval	*time;
	t_tstate		*th_s;

	th_s = malloc(sizeof(struct thread_state));
	time = malloc(sizeof(struct timeval));
	if (!th_s || !time)
		return (NULL);
	if (gettimeofday(time, NULL))
		return (NULL);
	th_s->v = copy(v);
	th_s->st_time = time->tv_sec;
	th_s->compilation_times = 0;
	th_s->is_alive = 1;
	th_s->coder_num = num;
	if (pthread_mutex_init(&(th_s->st_mutex), NULL) != 0)
		return (NULL);
	free(time);
	return ((void *)th_s);
}
