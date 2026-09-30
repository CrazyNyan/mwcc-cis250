#ifndef __STRING_VECTOR_H__
#define __STRING_VECTOR_H__
 
#include <stddef.h>
 
typedef struct {
    char **data;      // Pointer to an array of char pointers (strings)
    size_t capacity;  // Maximum number of elements before resizing
    size_t size;      // Current number of elements stored
} StringVector;
 
// Function Prototypes
StringVector* vector_create(size_t initial_capacity);
int vector_push(StringVector *vec, const char *str);
const char* vector_get(const StringVector *vec, size_t index);
void vector_free(StringVector *vec);
 
#endif
