/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/10 14:00:48 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	init_val(t_vars *v)
{
	v->sim_state = malloc(sizeof(int));
	*v->sim_state = 1;
	v->st_run = get_start_time();
}

void	do_one_case(time_t burnout, int coder_num)
{
	if (coder_num != 1)
	{
		printf("Number os coders must be grater than 1.\n");
		return ;
	}
	printf("%ld %i has taken a dongle\n", (time_t)0, 1);
	usleep(burnout);
	printf("%li %i burned out\n", burnout, 1);
}

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
		do_one_case(v->time_to_burnout, v->number_of_coders);
		free(v);
		return (0);
	}
	init_val(v);
	thread_init(v);
	return (0);
}
