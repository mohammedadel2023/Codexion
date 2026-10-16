/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 15:40:16 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/16 17:29:48 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	queue_assign(t_queue *myqu, t_queue_el **qu, int *buffer)
{
	myqu->qu = qu;
	myqu->buffer = buffer;
	myqu->els_num = 0;
	myqu->full_els_num = 0;
	myqu->buffer_eln = 0;
}

t_queue	*create_queue(int size)
{
	t_queue		*myqu;
	t_queue_el	**qu;
	int			*buffer;

	if (size <= 0)
		return (NULL);
	myqu = malloc(sizeof(t_queue));
	qu = malloc(sizeof(t_queue_el *) * size);
	if (!myqu || !qu)
	{
		free(myqu);
		free(qu);
		return (NULL);
	}
	buffer = malloc(sizeof(int) * size);
	if (!buffer)
	{
		free(myqu);
		free(qu);
		return (NULL);
	}
	queue_assign(myqu, qu, buffer);
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
