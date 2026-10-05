#include "codexion.h"

pthread_mutex_t m;

int	main(int argc, char **argv)
{
	t_queue	*myqu;
	t_tstate	t1;
	t_tstate	t2;
	t_tstate	t3;
	t_vars			*v;

	v = malloc(sizeof(t_vars));
	if (!v)
		return (1);
	if (!parser(argc, argv, v))
	{
		printf("Parssing issue pls check it.\n");
		free(v);
		return (0);
	}
	printf("parsing done\n");
	t1.coder_num = 1;
	t1.st_time = (time_t)4;
	t1.v = v;
	t2.coder_num = 2;
	t2.st_time = (time_t)10;
	t2.v = v;
	t3.coder_num = 3;
	t3.st_time = (time_t)2;
	t3.v = v;
	printf("%i\n",t1.st_time > t3.st_time);

	printf("assgin done\n");
	myqu = create_queue(v->number_of_coders);
	printf("create queue\n");
	push(&t1, fifo, myqu);
	push(&t2, fifo, myqu);
	push(&t3, fifo, myqu);
	printf("push el\n");
	printf("the queue include {%i} coder with size [%i]\n", myqu->qu[0]->coder_num, myqu->els_num);
	printf("the top coder is [%i]\n", pull(myqu));
	printf("the top coder is [%i]\n", pull(myqu));
	printf("the top coder is [%i]\n", pull(myqu));
	free_queue(myqu);
	printf("free all\n");
	free(v);
}
