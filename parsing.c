/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:12:29 by mkhashan          #+#    #+#             */
/*   Updated: 2026/09/26 00:08:19 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	*num_val(char	*str)
{
	int	*res;

	res = malloc(sizeof(int));
	if (!res)
		return (-1);
	*res = atoi(str);
	return (res);
}

void	*check_val(char	*str, char	*type)
{
	void	*res;

	if (type == "num")
	{
		res = (void *)num_val(str);
		if (*(int *)res == -1)
			return (NULL);
		return (res);
	}
	else if (type == "time")
	{
		res = (void *)num_val(str);
		if (*(int *)res == -1)
			return (NULL);
		return (res);
	}
	else if (type == "policy")
	{
		if (strcmp(str, "fifo") == 0)
			return (void *)fifo;
		else if (strcmp(str, "edf") == 0)
			return (void *)edf;
		return (NULL);
	}
	return (NULL);
}

int	parser(int	argc, char	**argv)
{
    int			it;
    struct vars	v;
    
    it = 1;
    if (argc != 17)
    {
        printf("Args issue check your args");
        return (0);
    }
    while (it < argc)
    {
        if (argv[it] == "number_of_coders" && check_val(argv[it + 1], "num"))
            v.number_of_coders = *(int *)check_val(argv[it + 1], "num");
        else if (argv[it] == "number_of_compiles_required" && check_val(argv[it + 1], "num"))
            v.number_of_compiles_required = *(int *)check_val(argv[it + 1], "num");
        else if (argv[it] == "time_to_burnout" && check_val(argv[it + 1], "time"))
            v.time_to_burnout = *(struct timespec *)check_val(argv[it + 1], "time");
        else if (argv[it] == "time_to_compile" && check_val(argv[it + 1], "time"))
            v.time_to_compile = *(struct timespec *)check_val(argv[it + 1], "time");
        else if (argv[it] == "time_to_debug" && check_val(argv[it + 1], "time"))
            v.time_to_debug = *(struct timespec *)check_val(argv[it + 1], "time");
        else if (argv[it] == "time_to_refactor" && check_val(argv[it + 1], "time"))
            v.time_to_refactor = *(struct timespec *)check_val(argv[it + 1], "time");
        else if (argv[it] == "dongle_cooldown" && check_val(argv[it + 1], "time"))
            v.dongle_cooldown = *(struct timespec *)check_val(argv[it + 1], "time");
        else if (argv[it] == "scheduler" && check_val(argv[it + 1], "policy"))
            v.scheduler = *(enum policy *)check_val(argv[it + 1], "policy");
        printf("Undefined arg '%s'.", argv[it]);
        return (0);
    }
    return (1);
}