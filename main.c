/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/08 14:57:11 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_vars	*v;

	v = malloc(sizeof(t_vars));
	if (!v)
		return (1);
	if (parser(argc, argv, v) != 0)
	{
		printf("Parssing issue pls check it.\n");
		free(v);
		return (0);
	}
	// thread_init(v);
	free(v);
	return (0);
}
