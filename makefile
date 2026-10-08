compile:
	cc -g main.c parsing.c threading.c threading_utlis.c utlis.c coder.c queue_utlis.c queue_push.c queue_pull.c -o mm
run:
	./mm 5  1200  1  1  1  1  1  edf
clean:
	rm mm
	rm *.o

valgrind: mm
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./mm number_of_compiles_required 5 time_to_burnout 3000 time_to_compile 45 number_of_coders 5 time_to_debug 12 time_to_refactor 45 dongle_cooldown 1 scheduler edf