/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threading.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 09:44:03 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/01 14:02:21 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


void	*coder(void *args)
{
	struct timeval t;
	struct thread_state *th_s;

	th_s = (struct thread_state *)args;
	while (th_s->compilation_times != th_s->v->number_of_compiles_required &&
			th_s->is_alive != 0)
	{
		printf("start thread %i \n", th_s->coder_num);
		sleep(1);
		th_s->compilation_times++;
		printf("added");
		pthread_mutex_lock(&(th_s->st_mutex));
		if (gettimeofday(&t, NULL) != 0)
			return (NULL);
		th_s->st_time = t.tv_sec;
		printf("the %i coder  run for the %i int time and the time start is:%i\n", th_s->coder_num, th_s->compilation_times, th_s->st_time);
		pthread_mutex_unlock(&(th_s->st_mutex));
		
	}
	free(th_s);
}


int	is_live(struct thread_state **th_s)
{
	int	it;

	it = 0;
	while (th_s[it])
	{
		if (th_s[it]->is_alive == 1)
			return (1);
		it++;
	}
	return (0);
}

void	*thread_monitor(void *args)
{
	int	it;
	struct timeval	t;
	struct thread_state **th_s;

	th_s = (struct thread_state **)args;
	while (is_live(th_s))
	{
		it = 0;
		while (th_s[it])
		{
			if (gettimeofday(&t, NULL) == 0)
			{
				pthread_mutex_lock(&(th_s[it]->st_mutex));
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
			it++;
		}
	}
	return (NULL);
}

int	thread_init(struct vars *vars)
{
	int			initiated_coder;
	pthread_t	ths[vars->number_of_coders];
	pthread_t	monitor_th;
	struct thread_state *th_s[vars->number_of_coders];
	//struct thread_state *th_s;
	struct timeval		*time;
	
	initiated_coder = 0;
	printf("start initiate\n");
	while (initiated_coder < vars->number_of_coders)
	{
		th_s[initiated_coder] = malloc(sizeof(struct thread_state));
		time = malloc(sizeof(struct timeval));
		if (!th_s || !time)
			return (1);
		if (gettimeofday(time, NULL))
		{
			return (2);
		}
		th_s[initiated_coder]->v = vars;
		th_s[initiated_coder]->st_time = time->tv_sec;
		th_s[initiated_coder]->compilation_times = 0;
		th_s[initiated_coder]->is_alive = 1;
		th_s[initiated_coder]->coder_num = initiated_coder;
		if ((pthread_mutex_init(&(th_s[initiated_coder]->st_mutex), NULL) != 0) ||
				pthread_create(&ths[initiated_coder], NULL, &coder, (void *)th_s[initiated_coder]) != 0)
			return (3);
		printf("create the %i thread\n", initiated_coder);
		initiated_coder++;
	}
	if (pthread_create(&monitor_th, NULL, &thread_monitor, (void *)th_s) != 0)
		return (5);
	printf("monitor thread was created\n");
	initiated_coder = 0;
	while (initiated_coder < vars->number_of_coders)
	{
		printf("start join coder %i\n", initiated_coder);
		pthread_join(ths[initiated_coder], NULL);
		printf("join the %i thread\n", initiated_coder);
		
		initiated_coder++;
	}
	pthread_join(monitor_th, NULL);
	printf("monitor thread joined");
	return (1);
	
}