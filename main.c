/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/13 13:39:47 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	sub_parseing(t_vars *v, int argc, char **argv)
{
	int		it;

	it = 1;
	while (it < argc - 3)
	{
		if (it == 1 && get_number_val(argv[it]) != -1)
			(*v).number_of_coders = get_number_val(argv[it]);
		else if (it == 2 && get_time_val(argv[it]) != -1)
			(*v).time_to_burnout = get_time_val(argv[it]);
		else if (it == 3 && get_time_val(argv[it]) != -1)
			(*v).time_to_compile = get_time_val(argv[it]);
		else if (it == 4 && get_time_val(argv[it]) != -1)
			(*v).time_to_debug = get_time_val(argv[it]);
		else if (it == 5 && get_time_val(argv[it]) != -1)
			(*v).time_to_refactor = get_time_val(argv[it]);
		else
			return (1);
		it++;
	}
	return (0);
}

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
	usleep(burnout * 1000);
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
		printf("args error\n");
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
	if (thread_init(v) != 0)
		return (0);
	return (0);
}
