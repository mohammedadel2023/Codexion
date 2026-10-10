/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/10 12:20:09 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char **argv)
{
	t_vars	*v;
	int		parse_res;

	v = malloc(sizeof(t_vars));
	if (!v)
		return (1);
	parse_res = parser(argc, argv, v);
	if (parse_res == 1)
	{
		printf("there is extra or missing args.\n");
		free(v);
		return (0);
	}
	if (v->number_of_coders <= 1)
	{
		printf("Number os coders must be grater than 1.\n");
		free(v);
		return (0);
	}
	v->sim_state = malloc(sizeof(int));
	*v->sim_state = 1;
	v->st_run = get_start_time();
	thread_init(v);
	return (0);
}
