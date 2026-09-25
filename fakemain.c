/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhashan <mkhashan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/25 14:21:00 by mkhashan          #+#    #+#             */
/*   Updated: 2026/09/25 14:49:00 by mkhashan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int primes[10] = {1, 3, 5, 7, 9, 13, 17, 19, 23, 27};

void	*tst(void	*args){

	printf(" %i ", *(int *)args);
	return NULL;
}

int main(int	argc, char	**argv){
	pthread_t th[10];
	int	*a;
	for (int i = 0; i < 10; i++){
		a = malloc(sizeof(*a));
		*a = i;
		// printf("the vale %i \n",*(primes + *a));
		pthread_create(&th[i], NULL, &tst, (primes + *a));
	}
	for (int i = 0; i < 10; i++){
		pthread_join(th[i], NULL);
	}
	return (0);
}