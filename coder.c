/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:07:04 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 15:48:15 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	is_burnout(time_t time, t_tstate *th_s)
{
	pthread_mutex_lock(&(th_s->st_mutex));
	if (time - th_s->st_time
		>= th_s->v->time_to_burnout)
	{
		th_s->is_alive = 0;
		printf("%i %i burned out\n", time, th_s->coder_num);
	}
	else if (th_s->compilation_times
		== th_s->v->time_to_burnout)
		th_s->is_alive = 0;
	pthread_mutex_unlock(&(th_s->st_mutex));
}

void	*coder(void *args)
{
	struct timeval	t;
	t_tstate		*th_s;

	th_s = (t_tstate *)args;
	while (th_s->is_alive != 0 && th_s->compilation_times
		!= th_s->v->number_of_compiles_required)
	{
		sleep(1);
		pthread_mutex_lock(&(th_s->st_mutex));
		th_s->compilation_times++;
		if (gettimeofday(&t, NULL) != 0)
			return (NULL);
		th_s->st_time = t.tv_sec;
		pthread_mutex_unlock(&(th_s->st_mutex));
	}
	printf("the %i coder stop\n", th_s->coder_num);
	th_s->is_alive = -1;
}
