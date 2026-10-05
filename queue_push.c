/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 17:13:38 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 15:41:49 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heapify_up(t_queue *myqu)
{
	int			index;
	t_queue_el	*buffer;

	index = myqu->els_num - 1;
	while (index != 0 && myqu->qu[index]->coder_wight
		< myqu->qu[parent(index)]->coder_num)
	{
		buffer = myqu->qu[index];
		myqu->qu[index] = myqu->qu[parent(index)];
		myqu->qu[parent(index)] = buffer;
		index = parent(index);
	}
}

void	hide_push(t_queue *myqu, t_queue_el *q_el, t_policy policy)
{
	myqu->qu[myqu->els_num - 1] = q_el;
	if (policy == edf)
		heapify_up(myqu);
}

int	push(t_tstate *th_s, t_policy policy, void	*queue)
{
	t_queue		*myqu;
	t_queue_el	*q_el;

	if (queue == NULL)
		create_queue(&queue, th_s[0].v->number_of_coders);
	myqu = (t_queue *) queue;
	q_el = malloc(sizeof(t_queue));
	if (!q_el)
		return (-1);
	if (policy == fifo)
		q_el->coder_wight = 0;
	else
		q_el->coder_wight = calc_wight(th_s);
	q_el->coder_num = th_s->coder_num;
	myqu->els_num++;
	hide_push(myqu, q_el, policy);
}
