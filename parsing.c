/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:12:29 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/11 14:38:31 by mkhashan         ###   ########.fr       */
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

int	get_policy_val(char *str)
{
	if (!str)
		return (0);
	if (strcmp(str, "fifo") == 0)
		return (0);
	else if (strcmp(str, "edf") == 0)
		return (0);
	else
		return (-1);
}

int	parser(int argc, char **argv, t_vars *v)
{
	int		it;

	it = 5;
	if (argc != 9)
		return (1);
	if (sub_parseing(v, argc, argv) != 0)
		return (1);
	while (++it < argc)
	{
		if (it == 6 && get_number_val(argv[it]) != -1)
			(*v).number_of_compiles_required = get_number_val(argv[it]);
		else if (it == 7 && get_time_val(argv[it]) != -1)
			(*v).dongle_cooldown = get_time_val(argv[it]);
		else if (it == 8 && get_policy_val(argv[it]) == 0)
			if (strcmp(argv[it], "fifo") == 0)
				(*v).scheduler = fifo;
			else
				(*v).scheduler = edf;
		else
			return (1);
	}
	return (0);
}
