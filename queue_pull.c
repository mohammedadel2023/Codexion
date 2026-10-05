/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_pull.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 16:56:35 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 18:41:05 by mkhashan         ###   ########.fr       */
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

int	heapify_down(t_queue *myqu)
{
	int			index;
	int			smallest;
	int			left;
	int			right;
	t_queue_el	*buffer;

	index = 0;
	smallest = index;
	while (1)
	{
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

int	get_top(t_queue *myqu)
{
	int	top_coder;

	top_coder = myqu->qu[0]->coder_num;
	free(myqu->qu[0]);
	if (myqu->els_num == 1)
	{
		myqu->qu[0] == NULL;
		myqu->els_num--;
	}
	else
	{
		myqu->qu[0] = myqu->qu[myqu->els_num - 1];
		myqu->qu[myqu->els_num - 1] = NULL;
		myqu->els_num--;
		heapify_down(myqu);
	}
	return (top_coder);
}

int	pull(t_queue *myqu)
{
	if (!myqu)
		return (-1);
	if (!(myqu->els_num > 0))
		return (-2);
	return (get_top(myqu));
}
