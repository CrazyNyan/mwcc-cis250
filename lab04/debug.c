#include <stdio.h>
#include <stdlib.h>

int calculate_sum(int *numbers, int size){
	int sum = 0;

	for (int i = 0; i < size; i++){
		sum += numbers[i];
	}

	return sum;
}

double calculate_average(int sum, int size){
	return sum / size;
}

int main(void){
	int size = 5;

	int numbers[] = {10, 20, 30, 40, 50};

	int *copy = malloc(size * sizeof(int));

	for (int i = 0; i < size; i++){
		copy[i] = numbers[i];
	}

	int sum = calculate_sum(numbers, size);
	double average = calculate_average(sum, size);

	printf("Numbers: ");

	for (int i = 0; i < size; i++){
		printf("%d ", copy[i]);
	}

	printf("\n");
	printf("Sum: %d\n", sum);
	printf("Average: %.2f\n", average);

	free(copy);
	return 0;
}
