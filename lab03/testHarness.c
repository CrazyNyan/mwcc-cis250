#include <stdio.h>
#include "string_vector.h"
 
int main(void) {

	StringVector *vec = vector_create(2); // Start with small capacity to force resizing

	vector_push(vec, "Hello");
	vector_push(vec, "World");
	vector_push(vec, "Pointers"); // Triggers realloc
	vector_push(vec, "Dynamic Memory");
 
	for (size_t i = 0; i < vec->size; i++) {
	printf("[%zu] %s\n", i, vector_get(vec, i));
	}
 
	vector_free(vec);
	return 0;
}
