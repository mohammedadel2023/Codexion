/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 16:56:35 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/16 17:06:13 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	swap_q_el(t_queue *myqu, int index, int smallest)
{
	t_queue_el	*buffer;

	buffer = myqu->qu[index];
	myqu->qu[index] = myqu->qu[smallest];
	myqu->qu[smallest] = buffer;
	index = smallest;
	return (smallest);
}

void	heapify_down(t_queue *myqu, int index)
{
	int			smallest;
	int			left;
	int			right;

	smallest = index;
	while (1)
	{
		smallest = index;
		left = l_child(index);
		right = r_child(index);
		if (left < myqu->els_num && myqu->qu[left]->coder_wight
			< myqu->qu[smallest]->coder_wight)
			smallest = left;
		if (right < myqu->els_num && myqu->qu[right]->coder_wight
			< myqu->qu[smallest]->coder_wight)
			smallest = right;
		if (smallest != index)
			index = swap_q_el(myqu, index, smallest);
		else
			break ;
	}
}

int	pull(t_queue *myqu, t_dongles *dongle, t_vars v)
{
	int	top_coder;

	if (!myqu || !dongle || !v.sim_state || myqu->els_num == 0
		|| !myqu->buffer)
		return (-1);
	top_coder = myqu->qu[0]->coder_num;
	free(myqu->qu[0]);
	myqu->els_num--;
	if (myqu->els_num == 0)
		myqu->qu[0] = NULL;
	else
	{
		myqu->qu[0] = myqu->qu[myqu->els_num];
		myqu->qu[myqu->els_num] = NULL;
		heapify_down(myqu, 0);
	}
	if (is_dongle_free(top_coder - 1, dongle, v) != 1)
	{
		myqu->buffer[myqu->buffer_eln++] = top_coder;
		return (-1 * top_coder);
	}
	return (top_coder);
}

void	enqueue_ready(t_queue *myqu, t_tstate **th_s, int size)
{
	int	it;

	it = 0;
	while (it < size)
	{
		pthread_mutex_lock(&th_s[it]->st_mutex);
		if (th_s[it]->is_alive == 2 && !th_s[it]->is_queued
			&& push(th_s[it], th_s[it]->v->scheduler, myqu) == 0)
			th_s[it]->is_queued = 1;
		pthread_mutex_unlock(&th_s[it]->st_mutex);
		it++;
	}
}

void	reset_buffer(t_queue *myqu, t_tstate **th_s)
{
	int			it;
	int			coder;
	t_policy	policy;

	policy = th_s[0]->v->scheduler;
	it = 0;
	while (it < myqu->buffer_eln)
	{
		coder = myqu->buffer[it];
		push(th_s[coder - 1], policy, myqu);
		myqu->buffer[it] = 0;
		it++;
	}
	myqu->buffer_eln = 0;
}
