/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:12:29 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/09 14:26:28 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

time_t	get_time_val(char *str)
{
	long	val;

	if (!str)
		return (-1);
	val = atoi(str);
	if (val < 0)
		return (-1);
	return ((time_t) val);
}

time_t	get_start_time(void)
{
	struct timeval	*time;
	time_t			milit_time;

	time = malloc(sizeof(struct timeval));
	if (!time)
		return (-1);
	if (gettimeofday(time, NULL))
		return (-1);
	milit_time = time->tv_sec * 1000 + time->tv_usec / 1000;
	free(time);
	return (milit_time);
}

int	get_number_val(char *str)
{
	int	num;

	if (!str)
		return (-1);
	num = atoi(str);
	if (num < 0)
		return (-1);
	return (num);
}

t_policy	get_policy_val(char *str)
{
	if (!str)
		return (0);
	if (strcmp(str, "fifo") == 0)
		return (fifo);
	else if (strcmp(str, "edf") == 0)
		return (edf);
	else
		return (-1);
}

int	parser(int argc, char **argv, t_vars *v)
{
	int		it;
	char	*str;

	it = 1;
	if (argc != 9)
	{
		printf("Args issue check your args\n");
		return (1);
	}
	while (it < argc)
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
		else if (it == 6 && get_number_val(argv[it]) != -1)
			(*v).number_of_compiles_required = get_number_val(argv[it]);
		else if (it == 7 && get_time_val(argv[it]) != -1)
			(*v).dongle_cooldown = get_time_val(argv[it]);
		else if (it == 8 && get_policy_val(argv[it]) != -1)
			(*v).scheduler = get_policy_val(argv[it]);
		else
		{
			printf("Undefined arg '%s'.\n", argv[it]);
			return (2);
		}
		it++;
	}
	if (v->number_of_coders < 1)
	{
		printf("Number os coders must be grater than 0.\n");
		return (3);
	}
	v->st_run = get_start_time();
	return (0);
}
