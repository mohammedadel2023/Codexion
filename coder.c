/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 18:07:04 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 18:08:24 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
	th_s->is_alive = -1;
	printf("the %i coder stop\n", th_s->coder_num);
}