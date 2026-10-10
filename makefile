compile:
	cc -g main.c parsing.c threading.c threading_utlis.c threading_main.c utlis.c coder.c queue_utlis.c queue_push.c queue_pull.c -o mm
run:
	./mm 5 500 100 100 100 3 10 edf
clean:
	rm mm
	rm *.o

valgrind: mm
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./mm 5  1200  5  100  30  1  3  fifo