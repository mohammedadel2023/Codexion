/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 15:28:43 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void	*coder(void *args)
{
	struct timeval t;
	t_tstate *th_s;

	th_s = (t_tstate *)args;
	while (th_s->is_alive != 0 &&
			th_s->compilation_times != th_s->v->number_of_compiles_required)
	{
		//printf("start thread %i \n", th_s->coder_num);
		sleep(5);
		//printf("added");
		pthread_mutex_lock(&(th_s->st_mutex));
		th_s->compilation_times++;
		if (gettimeofday(&t, NULL) != 0)
			return (NULL);
		th_s->st_time = t.tv_sec;
		//printf("the %i coder  run for the %i int time and the time start is:%i\n", th_s->coder_num, th_s->compilation_times, th_s->st_time);
		//th_s->v->stoped_coder += 1;
		pthread_mutex_unlock(&(th_s->st_mutex));
		
	}
	th_s->is_alive = -1;
	printf("the %i coder stop\n", th_s->coder_num);
	th_s;
}


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


struct vars *copy(t_vars *v)
{
	t_vars *new_v;

	new_v = malloc(sizeof(struct vars));
	*new_v = *v;
	return new_v;
}

int	free_thread(t_tstate **th_s)
{
	int	it;

	if (!th_s){
		return (0);
	}
	it = th_s[0]->v->number_of_coders;
	//free(th_s[0]->v->stoped_coder);
	while (0 <= it - 1)
	{
		free(th_s[it - 1]->v);
		free(th_s[it - 1]);
		it--;
	}
	return (1);
}

void	*thread_monitor(void *args)
{
	int	it;
	struct timeval	t;
	t_tstate **th_s;

	th_s = (struct thread_state **)args;
	while (is_live(th_s, 1))
	{
		it = 0;
		while (it < (th_s[0]->v->number_of_coders))
		{
			if (th_s[it]->is_alive)
			{
				if (gettimeofday(&t, NULL) == 0)
				{
					pthread_mutex_lock(&(th_s[it]->st_mutex));
					//printf("[coder %i]the time_to_burnout %i \n",th_s[it]->coder_num,  th_s[it]->v->time_to_burnout);
					//printf("[coder %i] the start time %i \n",th_s[it]->coder_num, th_s[it]->st_time);
					//printf("[coder %i] the t.tv_sec: %i \n",th_s[it]->coder_num, t.tv_sec);
					if (t.tv_sec - th_s[it]->st_time >= th_s[it]->v->time_to_burnout)
					{
						th_s[it]->is_alive = 0;
						printf("%i %i burned out\n", t.tv_sec, it);
					}
					else if (th_s[it]->compilation_times == th_s[it]->v->time_to_burnout)
					{
						th_s[it]->is_alive = 0;
					}
					pthread_mutex_unlock(&(th_s[it]->st_mutex));
				}
			}
			it++;
		}
	}
	while(is_live(th_s, 0))
	{
		usleep(1);
	}
	printf("monitor thread stoped\n");
	free_thread(th_s);
	return (NULL);
}

int	thread_init(t_vars *vars)
{
	int				initiated_coder;
	pthread_t		ths[vars->number_of_coders];
	pthread_t		monitor_th;
	t_tstate 		*th_s[vars->number_of_coders];
	struct timeval	*time;
	
	initiated_coder = 0;
	while (initiated_coder < vars->number_of_coders)
	{
		th_s[initiated_coder] = malloc(sizeof(struct thread_state));
		time = malloc(sizeof(struct timeval));
		if (!th_s || !time)
			return (1);
		if (gettimeofday(time, NULL))
			return (2);
		th_s[initiated_coder]->v = copy(vars);
		th_s[initiated_coder]->st_time = time->tv_sec;
		th_s[initiated_coder]->compilation_times = 0;
		th_s[initiated_coder]->is_alive = 1;
		th_s[initiated_coder]->coder_num = initiated_coder;
		if ((pthread_mutex_init(&(th_s[initiated_coder]->st_mutex), NULL) != 0) ||
				pthread_create(&ths[initiated_coder], NULL, &coder, (void *)th_s[initiated_coder]) != 0)
			return (3);
		//printf("create the %i thread\n", initiated_coder);
		initiated_coder++;
		free(time);
	}
	if (pthread_create(&monitor_th, NULL, &thread_monitor, (void *)th_s) != 0)
		return (5);
	initiated_coder = 0;
	while (initiated_coder < vars->number_of_coders)
	{
		pthread_join(ths[initiated_coder], NULL);
		//printf("join the %i thread\n", initiated_coder);
		initiated_coder++;
	}
	pthread_join(monitor_th, NULL);
	return (1);
}