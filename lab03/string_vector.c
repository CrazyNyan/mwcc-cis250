#include "string_vector.h"
#include <stdlib.h>
#include <string.h>

// Creation function
StringVector* vector_create(size_t inital_capacity){
	// Create the vector struct
	StringVector *vec = malloc(sizeof(StringVector));// + (inital_capacity * sizeof(char*)));
	// Assign values
	vec->capacity = inital_capacity;
	vec->size = 0;
	vec->data = malloc(inital_capacity * sizeof(char*));
	return vec;
}

// Adding a string to the vector
int vector_push(StringVector *vec, const char *str){
	// Check to see if the push is within the currect capacity
	if (vec->capacity == vec->size){
		//vec = realloc(vec, (sizeof(StringVector) + (vec->capacity * 2 * sizeof(char*))));
		vec->data = realloc(vec->data, (vec->capacity * 2 * sizeof(char*)));
	}
	// Allocate the memory within the data array and write the string there
	vec->data[vec->size] = malloc(sizeof(*str + 1));
	strcpy(vec->data[vec->size], str);

	vec->size++;
	return 1;
}

// Getting a string from the vector
const char* vector_get(const StringVector *vec, size_t index){
	// Check if the index is within the bounds of the vector
	if (index >= vec->size){
	return NULL;
	}
	
	// Return the pointer at the index
	return vec->data[index];
}

// Freeing the vector
void vector_free(StringVector *vec){
	// Increment through each pointer in data and free it
	for (int i = 0; i < (int)vec->size - 1; i++){
		free(vec->data[i]);
	}
	// Free data
	free(vec->data);
	// Free the vector
	free(vec);
}
