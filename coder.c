/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:07:04 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/07 17:53:15 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	is_burnout(time_t time, t_tstate *th_s, t_queue *myqu)
{
	time_t	conv_time;

	conv_time = (time * 1000) - th_s->v->st_run;
	printf("enter the is_burnout\n");
	pthread_mutex_lock(&(th_s->st_mutex));
	if (conv_time - th_s->st_time
		>= th_s->v->time_to_burnout)
	{
		th_s->is_alive = 0;
		printf("%i %i burned out\n", conv_time, th_s->coder_num);
	}
	if (th_s->is_alive == 2)
	{
		printf("the coder [%i] was pushed\n", th_s->coder_num);
		push(th_s, th_s->v->scheduler, myqu);
		th_s->is_alive = 1;
	}
	pthread_mutex_unlock(&(th_s->st_mutex));
}

void	coder_compile(t_tstate *th_s)
{
	pthread_mutex_lock(&th_s->lift_d->dong_mutex);
	printf("%i %i has taken a dongle", th_s->st_time, th_s->coder_num);
	pthread_mutex_lock(&th_s->right_d->dong_mutex);
	printf("%i %i has taken a dongle", th_s->st_time, th_s->coder_num);
	printf("%i %i is compiling", th_s->st_time, th_s->coder_num);
	usleep(th_s->v->time_to_compile * 1000);
	pthread_mutex_unlock(&th_s->lift_d->dong_mutex);
	th_s->lift_d->state = 1;
	pthread_mutex_unlock(&th_s->right_d->dong_mutex);
	th_s->right_d->state = 1;
}

void	*coder(void *args)
{
	struct timeval	t;
	t_tstate		*th_s;

	th_s = (t_tstate *)args;
	printf("the coder [%i] is ready to enter the loop\n", th_s->coder_num);
	pthread_mutex_lock(&(th_s->st_mutex));
	while (th_s->is_alive != 0 && th_s->compilation_times
		!= th_s->v->number_of_compiles_required)
	{
		th_s->is_alive = 2;
		pthread_cond_wait(&th_s->cond, &th_s->st_mutex);
		pthread_mutex_unlock(&(th_s->st_mutex));
		if (gettimeofday(&t, NULL) != 0)
			return (NULL);
		th_s->st_time = (t.tv_sec * 1000) + t.tv_usec / 1000 - th_s->v->st_run;
		pthread_mutex_lock(&(th_s->st_mutex));
		coder_compile(th_s);
		th_s->compilation_times++;
		printf("%i %i is debugging", th_s->st_time, th_s->coder_num);
		usleep(th_s->v->time_to_debug * 1000);
		printf("%i %i is refactoring", th_s->st_time, th_s->coder_num);
		usleep(th_s->v->time_to_refactor * 1000);
	}
	th_s->is_alive = -1;
	printf("the %i coder stop and the is_alive is [%i]\n", th_s->coder_num, th_s->is_alive);
	pthread_mutex_unlock(&(th_s->st_mutex));
}


