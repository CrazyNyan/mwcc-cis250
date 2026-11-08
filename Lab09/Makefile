build:
	gcc -Wall -Wextra sysmon.c -o sysmon

debug:
	gcc -g sysmon.c -o sysmon

memcheck:
	valgrind --leak-check=full --show-leak-kinds=all ./sysmon

clean:
	rm -f sysmon