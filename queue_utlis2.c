/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utlis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 16:56:35 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/04 17:25:03 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

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
		if (left < myqu->els_num &&
			myqu->qu[left]->coder_wight < myqu->qu[smallest]->coder_wight)
			smallest = left;
		if (left < myqu->els_num &&
			myqu->qu[right]->coder_wight < myqu->qu[smallest]->coder_wight)
			smallest = right;
		if (smallest != index)
		{
			buffer = myqu->qu[index];
			myqu->qu[index] = myqu->qu[smallest];
			myqu->qu[smallest] = buffer;
			index = smallest;
		}
		else
			break;
	}
}

void get_top(t_queue *myqu, t_policy policy)
{
	int	top_coder;

	top_coder = myqu->qu[0]->coder_num;
	if (myqu->els_num == 1)
	{
		myqu->qu[0] == NULL;
		myqu->els_num--;
		return;
	}
	else
	{
		myqu->qu[0] = myqu->qu[myqu->els_num - 1];
		heapify_down(myqu);
	}
}

int	pull(t_queue *myqu, t_policy policy)
{
	if (!myqu)
		return (-1);
	if (!(myqu->els_num > 0))
		return (-2);
	get_top(myqu, policy);
}