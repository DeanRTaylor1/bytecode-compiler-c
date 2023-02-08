#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

typedef enum {
  OP_RETURN,
} OpCode;

/* Dynamic array, keep the keep track of the capacity and the count of vals
if the arrays count is < capacity, we can add the item
if not, we create a new array with double the capacity, and copy the elements over to the new location in memory
This is pretty much how slices work in Go
Because we are doubling the size we are not copying the data every time which ensures
Big O of O(1) not O(n) see amortized analysis */

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte);

#endif
