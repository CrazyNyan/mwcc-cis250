build:
	gcc -Wall -Wextra copy.c -o copy2

debug:
	gcc -g copy.c -o copy

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./copy2

test:
	./copy2 source.txt target.txt

clean:
	rm copy2
