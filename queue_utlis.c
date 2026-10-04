/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/03 17:13:38 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/04 17:12:24 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_queue(void **queue, int size)
{
	t_queue		*myqu;
	t_queue_el	**qu;
	
	myqu = malloc(sizeof(t_queue));
	qu = malloc(sizeof(t_queue_el *) * size);
	if (!(qu) || !(myqu))
		return (-1);
	myqu->qu = qu;
	myqu->els_num = 0;
	*queue = myqu;
	return (0);
}

int	parent(int index)
{
	int	parent_index;

	parent_index = (index - 1) / 2;
	return (parent_index);
}

int	l_child(int index)
{
	int	lchiled_index;

	lchiled_index = (index * 2) + 1;
	return (lchiled_index);
}

int	r_child(int index)
{
	int	rchiled_index;

	rchiled_index = (index * 2) + 2;
	return (rchiled_index);
}

int	heapify_up(t_queue *myqu)
{
	int			index;
	t_queue_el	*buffer;

	index = myqu->els_num - 1;
	while (index != 0 &&
		myqu->qu[index]->coder_wight < myqu->qu[parent(index)]->coder_num)
	{
		buffer = myqu->qu[index];
		myqu->qu[index] = myqu->qu[parent(index)];
		myqu->qu[parent(index)] = buffer;
		index = parent(index);
	}
}

int	calc_wight(t_tstate *th_s)
{
	int	wight;

	wight = 0;
	wight = th_s->st_time + th_s->v->time_to_burnout;
	return (wight);
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
