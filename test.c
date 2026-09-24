#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

int mails = 0;

void	*tst(void *mtx){

	pthread_mutex_lock((pthread_mutex_t *) mtx);
	// *x = 4;
	for (int i = 0; i <100000; i++){
		mails++;
	}
	printf("the mails=%i", mails);
	pthread_mutex_unlock((pthread_mutex_t *) mtx);
	return NULL;
}

int	main(void){
	pthread_t	th1;
	pthread_t	th2;
	// int			*x;
	pthread_mutex_t mtx;

	pthread_mutex_init(&mtx, NULL);
	if (pthread_create(&th1, NULL, &tst, (void *) &mtx) != 0)
	{
		printf("failled");
		return (1);
	}
	printf("first_thread_created\n");
	if (pthread_create(&th2, NULL, &tst, (void *) &mtx) != 0)
	{
		return (2);
	}
	printf("second_thread_created\n");
	if (pthread_join(th1, NULL))
		return (3);
	// printf("the value of x:%i", *x);
	if (pthread_join(th2, NULL))
		return (4);
	// printf("the value of x:%i",*x);
	pthread_mutex_destroy(&mtx);
	return (0);
}