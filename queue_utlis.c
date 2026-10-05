/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 15:40:16 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/05 15:41:06 by mkhashan         ###   ########.fr       */
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

int	calc_wight(t_tstate *th_s)
{
	int	wight;

	wight = 0;
	wight = th_s->st_time + th_s->v->time_to_burnout;
	return (wight);
}
