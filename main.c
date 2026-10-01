/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/10/01 10:37:56 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int	argc, char	**argv){
	struct vars		*v;
	struct timeval	t;

	v = malloc(sizeof(*v));
	if (!v)
		return (1);
	if (!parser(argc, argv, v))
	{
		printf("Parssing issue pls check it.\n");
		return (0);
	}
	int x = gettimeofday(&t, NULL);
	/*if (!x)
	{
		printf("the times is: %i\n", t.tv_usec);
	}*/
	thread_init(v);
	//printf("%i\n",v->number_of_coders);
	//printf("%i\n",v->time_to_refactor);
	//printf("%i\n",v->scheduler);
	return (0);
}