compile:
	cc main.c parsing.c -o mm

run:
	./mm number_of_compiles_required 5 time_to_burnout 12 time_to_compile 45 number_of_coders 2 time_to_debug 12 time_to_refactor 45 dongle_cooldown 1 scheduler fifo

clean:
	rm mm
	rm *.o