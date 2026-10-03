/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:12:29 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 14:39:42 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


time_t get_time_val(char *str)
{
	long	val;

	if (!str)
		return (-1);
	val = atoi(str);
	if (val < 0)
		return (-1);
	return ((time_t) val);
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

e_policy get_policy_val(char *str)
{
	if (!str)
		return (0);
	if (strcmp(str, "fifo") == 0)
	{
		return (fifo);
	}
	else if (strcmp(str, "edf") == 0)
	{
		return (edf);
	}
	else
	{
		return (-1);
	}	
}

/*void	*num_val(char	*str, int	*res)
{
	*res = atoi(str);
	if (*res <= 0)
		return (NULL);
	return (res);
}

void	*check_val(char	*str, char	*type)
{
	void	*res;

	if (strcmp(type, "policy") == 0)
	{
		if (strcmp(str, "fifo") == 0)
		{
			// res = malloc(sizeof(enum policy));
			*(enum policy *)res = fifo;
			return (res);
		}
		else if (strcmp(str, "edf") == 0)
		{
			// res = malloc(sizeof(enum policy));
			*(enum policy *)res = edf;
			return (res);
		}
		return (NULL);
	}

	if (strcmp(type, "num") == 0)
	{
		res = (void *)num_val(str, (int *)res);
		if (!res)
			return (NULL);
		return (res);
	}
	else if (strcmp(type, "time") == 0)
	{
		res = (void *)num_val(str, (int *)res);
		if (!res)
			return (NULL);
		return (res);
	}
	else if (strcmp(type, "policy") == 0)
	{
		if (strcmp(str, "fifo") == 0)
		{
			// res = malloc(sizeof(enum policy));
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
}*/

int	parser(int argc, char **argv, t_vars *v)
{
	int		it;
	char	*str;
	int		*stoped_c;

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
			&& get_number_val(argv[it + 1]) != -1)
			(*v).number_of_coders =  get_number_val(argv[it + 1]);
		else if (strcmp(argv[it], "number_of_compiles_required") == 0
			&& get_number_val(argv[it + 1]) != -1)
			(*v).number_of_compiles_required = get_number_val(argv[it + 1]);
		else if (strcmp(argv[it] ,"time_to_burnout") == 0
			&& get_time_val(argv[it + 1]) != -1)
			(*v).time_to_burnout = get_time_val(argv[it + 1]);
		else if (strcmp(argv[it], "time_to_compile") == 0
			&& get_time_val(argv[it + 1]) != -1)
			(*v).time_to_compile =  get_time_val(argv[it + 1]);
		else if (strcmp(argv[it], "time_to_debug") == 0
			&& get_time_val(argv[it + 1]) != -1)
			(*v).time_to_debug =  get_time_val(argv[it + 1]);
		else if (strcmp(argv[it], "time_to_refactor") == 0
			&& get_time_val(argv[it + 1]) != -1)
			(*v).time_to_refactor =  get_time_val(argv[it + 1]);
		else if (strcmp(argv[it], "dongle_cooldown") == 0
			&& get_time_val(argv[it + 1]) != -1)
			(*v).dongle_cooldown =  get_time_val(argv[it + 1]);
		else if (strcmp(argv[it], "scheduler") == 0
			&& get_policy_val(argv[it + 1]) != -1)
		{
			(*v).scheduler =  get_policy_val(argv[it + 1]);
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
	//stoped_c = malloc(sizeof(int));
	//*stoped_c = 0; 
	//v->stoped_coder = stoped_c;
	return (1);
}
