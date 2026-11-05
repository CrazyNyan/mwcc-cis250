build:
	gcc -Wall -Wextra caseconv.c -o caseconv

clean:
	rm -f caseconv

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all -s ./caseconv upper testtext.txt

debug:
	gcc -g caseconv.c -o caseconv

test:
	./caseconv upper testtext.txt
