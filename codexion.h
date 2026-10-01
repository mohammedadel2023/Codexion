/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 23:10:53 by mkhashan          #+#    #+#             */
/*   Updated: 2026/09/26 14:07:53 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum policy{
	fifo = 1, edf = 2
};

typedef struct vars
{
	int	number_of_coders;
	struct timespec	time_to_burnout;
	struct timespec	time_to_compile;
	struct timespec	time_to_debug;
	struct timespec	time_to_refactor;
	int	number_of_compiles_required;
	struct timespec	dongle_cooldown;
	enum policy	scheduler;
}	t_vars;


int	parser(int argc, char **argv, struct vars *v);
