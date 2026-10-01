/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:11:51 by mkhashan          #+#    #+#             */
/*   Updated: 2026/09/26 14:03:46 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"


int	main(int	argc, char	**argv){
	struct vars	*v;

	v = malloc(sizeof(*v));
	if (!v)
		return (1);
	if (!parser(argc, argv, v))
	{
		printf("Parssing issue pls check it.\n");
		return (0);
	}
	// printf("%i\n",v->number_of_coders);
	// printf("%i\n",v->time_to_refactor);
	// printf("%i\n",v->scheduler);
	return (0);
}