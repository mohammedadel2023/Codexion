/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 17:13:38 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/04 15:51:36 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_queue(void **queue, int size)
{
	*queue = malloc(sizeof(t_queue_el *) * size);
	if (!(*queue))
		return (-1);
	return (0);
}

int	heapify_up();

int	calc_wight(t_tstate *th_s)
{
	int	wight;

	wight = 0;
	wight = th_s->st_time + th_s->v->time_to_burnout;
	return (wight);
}

void	hide_push(t_queue *myqu, t_queue_el *q_el)
{
	myqu->qu[myqu->els_num] = q_el;
	heapify_up();
}

int	push(t_tstate *th_s, t_policy policy, void	*queue)
{
	t_queue		*myqu;
	t_queue_el	*q_el;

	if (queue == NULL)
	{
		create_queue(&queue, th_s[0].v->number_of_coders);
		myqu->qu = (t_queue_el **) queue;
		myqu->els_num = 0;
	}
	q_el = malloc(sizeof(t_queue));
	if (!q_el)
		return (-1);
	if (policy == fifo)
		q_el->coder_wight = 0;
	else
		q_el->coder_wight = calc_wight(th_s);
	q_el->coder_num = th_s->coder_num;
	hide_push(myqu, q_el);
	myqu->els_num++;
}