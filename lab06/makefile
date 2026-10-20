build:
	gcc -Wall -Wextra test_runner.c -o test_runner

clean:
	rm -f test_runner

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all test_runner

debug:
	gcc -g test_runner.c -o test_runner
