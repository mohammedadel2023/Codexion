/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:07:04 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/10 14:02:07 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	is_burnout(struct timeval t, t_tstate *th_s, t_queue *myqu)
{
	time_t	conv_time;

	pthread_mutex_lock(&(th_s->st_mutex));
	conv_time = (t.tv_sec * 1000) + (t.tv_usec / 1000)
		- th_s->v->st_run;
	if (th_s->is_alive == -1)
	{
		pthread_mutex_unlock(&(th_s->st_mutex));
		return ;
	}
	if (conv_time - th_s->st_time
		>= th_s->v->time_to_burnout)
	{
		th_s->is_alive = 0;
		if (*th_s->v->sim_state)
			printf("%li %i burned out\n", conv_time, th_s->coder_num);
		*th_s->v->sim_state = 0;
	}
	else if (th_s->is_alive == 2)
	{
		push(th_s, th_s->v->scheduler, myqu);
		th_s->is_alive = 1;
	}
	pthread_mutex_unlock(&(th_s->st_mutex));
}

void	coder_compile(t_tstate *th_s)
{
	struct timeval	t;
	time_t			now;

	pthread_mutex_lock(&th_s->lift_d->dong_mutex);
	printf("%ld %i has taken a dongle\n", th_s->st_time, th_s->coder_num);
	pthread_mutex_lock(&th_s->right_d->dong_mutex);
	printf("%ld %i has taken a dongle\n", th_s->st_time, th_s->coder_num);
	th_s->lift_d->state = 0;
	th_s->right_d->state = 0;
	if (*th_s->v->sim_state == 1)
	{
		printf("%ld %i is compiling\n", th_s->st_time, th_s->coder_num);
		usleep(th_s->v->time_to_compile * 1000);
	}
	gettimeofday(&t, NULL);
	now = (t.tv_sec * 1000) + (t.tv_usec / 1000) - th_s->v->st_run;
	th_s->lift_d->last_used = now;
	th_s->right_d->last_used = now;
	th_s->lift_d->state = 1;
	th_s->right_d->state = 1;
	pthread_mutex_unlock(&th_s->lift_d->dong_mutex);
	pthread_mutex_unlock(&th_s->right_d->dong_mutex);
}

void	coder_op(t_tstate *th_s)
{
	if (*th_s->v->sim_state != 1)
		return ;
	coder_compile(th_s);
	th_s->compilation_times++;
	if (*th_s->v->sim_state)
	{
		printf("%ld %i is debugging\n", th_s->st_time
			+ th_s->v->time_to_compile, th_s->coder_num);
		usleep(th_s->v->time_to_debug * 1000);
	}
	if (*th_s->v->sim_state)
	{
		printf("%ld %i is refactoring\n", th_s->st_time + th_s->v->time_to_debug
			+ th_s->v->time_to_compile, th_s->coder_num);
		usleep(th_s->v->time_to_refactor * 1000);
	}
	pthread_mutex_lock(&th_s->st_mutex);
}

void	*coder(void *args)
{
	struct timeval	t;
	t_tstate		*th_s;

	th_s = (t_tstate *)args;
	pthread_mutex_lock(&th_s->st_mutex);
	while (th_s->is_alive != 0
		&& th_s->compilation_times != th_s->v->number_of_compiles_required
		&& *th_s->v->sim_state)
	{
		th_s->is_alive = 2;
		while (th_s->is_alive == 2)
			pthread_cond_wait(&th_s->cond, &th_s->st_mutex);
		if (gettimeofday(&t, NULL) != 0 || *th_s->v->sim_state != 1)
		{
			pthread_mutex_unlock(&th_s->st_mutex);
			th_s->is_alive = -1;
			return (NULL);
		}
		th_s->st_time = (t.tv_sec * 1000) + t.tv_usec / 1000 - th_s->v->st_run;
		pthread_mutex_unlock(&th_s->st_mutex);
		coder_op(th_s);
	}
	th_s->is_alive = -1;
	pthread_mutex_unlock(&th_s->st_mutex);
	return (NULL);
}
