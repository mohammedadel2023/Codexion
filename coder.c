/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:07:04 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/07 11:24:59 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	is_burnout(time_t time, t_tstate *th_s)
{
	time_t	conv_time;

	conv_time = (time * 1000) - th_s->v->st_run;
	pthread_mutex_lock(&(th_s->st_mutex));
	if (conv_time - th_s->st_time
		>= th_s->v->time_to_burnout)
	{
		th_s->is_alive = 0;
		printf("%i %i burned out\n", conv_time, th_s->coder_num);
	}
	pthread_mutex_unlock(&(th_s->st_mutex));
}

void	*coder(void *args)
{
	struct timeval	t;
	t_tstate		*th_s;

	th_s = (t_tstate *)args;
	pthread_mutex_lock(&(th_s->st_mutex));
	while (th_s->is_alive != 0 && th_s->compilation_times
		!= th_s->v->number_of_compiles_required)
	{
		pthread_mutex_unlock(&(th_s->st_mutex));
		if (gettimeofday(&t, NULL) != 0)
			return (NULL);
		th_s->st_time = (t.tv_sec * 1000) + t.tv_usec / 1000 - th_s->v->st_run;
		printf("the %i coder run for [%i] time at [%i]\n", th_s->coder_num, th_s->compilation_times, th_s->st_time);
		usleep(th_s->v->time_to_compile * 1000);
		th_s->compilation_times++;
		pthread_mutex_lock(&(th_s->st_mutex));
	}
	th_s->is_alive = -1;
	printf("the %i coder stop and the is_alive is [%i]\n", th_s->coder_num, th_s->is_alive);
	pthread_mutex_unlock(&(th_s->st_mutex));
}


