/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 15:40:16 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/06 16:35:31 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_queue	*create_queue(int size)
{
	t_queue		*myqu;
	t_queue_el	**qu;

	myqu = malloc(sizeof(t_queue));
	qu = malloc(sizeof(t_queue_el *) * size);
	if (!(myqu))
		return (NULL);
	myqu->qu = qu;
	myqu->els_num = 0;
	myqu->full_els_num = 0;
	return (myqu);
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
