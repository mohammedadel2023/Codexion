/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:12:29 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/01 13:33:22 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	*num_val(char	*str)
{
	int	*res;

	res = malloc(sizeof(int));
	if (!res)
		return (NULL);
	*res = atoi(str);
	if (*res <= 0)
		return (NULL);
	return (res);
}

void	*check_val(char	*str, char	*type)
{
	void	*res;

	if (strcmp(type, "num") == 0)
	{
		res = (void *)num_val(str);
		if (!res)
			return (NULL);
		return (res);
	}
	else if (strcmp(type, "time") == 0)
	{
		res = (void *)num_val(str);
		if (!res)
			return (NULL);
		return (res);
	}
	else if (strcmp(type, "policy") == 0)
	{
		if (strcmp(str, "fifo") == 0)
		{
			res = malloc(sizeof(enum policy));
			*(enum policy *)res = fifo;
			return (res);
		}
		else if (strcmp(str, "edf") == 0)
		{
			res = malloc(sizeof(enum policy));
			*(enum policy *)res = edf;
			return (res);
		}
		return (NULL);
	}
	return (NULL);
}

int	parser(int argc, char **argv, struct vars *v)
{
	int			it;
	char		*str;

	it = 1;
	if (argc != 17)
	{
		printf("Args issue check your args");
		return (0);
	}
	while (it < argc)
	{
		// printf("done --%s--\n", argv[it]);
		str = argv[it + 1];
		if (strcmp(argv[it], "number_of_coders") == 0
			&& check_val(argv[it + 1], "num"))
			(*v).number_of_coders = *(int *)check_val(argv[it + 1], "num");
		else if (strcmp(argv[it], "number_of_compiles_required") == 0
			&& check_val(argv[it + 1], "num") != NULL)
			(*v).number_of_compiles_required = *(int *)check_val(str, "num");
		else if (strcmp(argv[it] ,"time_to_burnout") == 0
			&& check_val(argv[it + 1], "time"))
			(*v).time_to_burnout = (time_t)check_val(str, "time");
		else if (strcmp(argv[it], "time_to_compile") == 0
			&& check_val(argv[it + 1], "time"))
			(*v).time_to_compile = (time_t)check_val(str, "time");
		else if (strcmp(argv[it], "time_to_debug") == 0
			&& check_val(argv[it + 1], "time"))
			(*v).time_to_debug = (time_t)check_val(str, "time");
		else if (strcmp(argv[it], "time_to_refactor") == 0
			&& check_val(argv[it + 1], "time"))
			(*v).time_to_refactor = (time_t)check_val(str, "time");
		else if (strcmp(argv[it], "dongle_cooldown") == 0
			&& check_val(argv[it + 1], "time"))
			(*v).dongle_cooldown = (time_t)check_val(str, "time");
		else if (strcmp(argv[it], "scheduler") == 0
			&& check_val(argv[it + 1], "policy"))
		{
			(*v).scheduler = *(enum policy *)check_val(str, "policy");
		}
		else {
			printf("Undefined arg '%s'.\n", argv[it]);
			return (0);
		}
		it += 2;
	}
	if (v->number_of_coders < 1)
	{
		printf("Number os coders must be grater than 0.\n");
		return (0);
	}
	return (1);
}
