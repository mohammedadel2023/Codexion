/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_push.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 17:13:38 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/06 16:35:58 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heapify_up(t_queue *myqu)
{
	int			index;

	index = myqu->els_num - 1;
	while (index != 0 && myqu->qu[index]->coder_wight
		< myqu->qu[parent(index)]->coder_wight)
		index = swap_q_el(myqu, index, parent(index));
}

void	hide_push(t_queue *myqu, t_queue_el *q_el, t_policy policy)
{
	myqu->qu[myqu->els_num - 1] = q_el;
	if (myqu->els_num > 1)
		heapify_up(myqu);
}

int	push(t_tstate *th_s, t_policy policy, t_queue	*myqu)
{
	t_queue_el	*q_el;

	if (!myqu || !th_s || !policy)
		return (-1);
	q_el = malloc(sizeof(t_queue));
	if (!q_el)
		return (-1);
	if (policy == fifo)
		q_el->coder_wight = myqu->full_els_num + 1;
	else
		q_el->coder_wight = calc_wight(th_s);
	q_el->coder_num = th_s->coder_num;
	myqu->els_num++;
	myqu->full_els_num++;
	hide_push(myqu, q_el, policy);
}

void	free_queue(t_queue *myqu)
{
	int	size;
	int	it;

	it = 0;
	size = myqu->els_num;

	while (it < size)
	{
		free(myqu->qu[it]);
		it++;
	}
	free(myqu->qu);
	free(myqu);
}
