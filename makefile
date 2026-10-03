compile:
	cc -g main.c parsing.c threading.c utlis.c coder.c -o mm
run:
	./mm number_of_compiles_required 5 time_to_burnout  7 time_to_compile 45 number_of_coders 5 time_to_debug 12 time_to_refactor 45 dongle_cooldown 1 scheduler edf
clean:
	rm mm
	rm *.o

valgrind: mm
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./mm number_of_compiles_required 5 time_to_burnout 12 time_to_compile 45 number_of_coders 5 time_to_debug 12 time_to_refactor 45 dongle_cooldown 1 scheduler edf