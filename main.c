/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/03 14:35:37 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int	argc, char	**argv){
	t_vars		*v;
	struct timeval	t;

	v = malloc(sizeof(t_vars));
	if (!v)
		return (1);
	if (!parser(argc, argv, v))
	{
		printf("Parssing issue pls check it.\n");
		free(v);
		return (0);
	}
	// int x = gettimeofday(&t, NULL);
	/*if (!x)
	{
		printf("the times is: %i\n", t.tv_usec);
	}*/
	thread_init(v);
	//free_v(v);
	//free(v);
	//printf("parssing done.\n");
	//printf("%i\n",v->number_of_coders);
	//printf("%i\n",v->time_to_refactor);
	//printf("%i\n",v->scheduler);
	//printf("%i\n",*(v->stoped_coder));
	//free(v->stoped_coder);
	free_v(v);
	return (0);
}