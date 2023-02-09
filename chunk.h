#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

//These are the types of the chunks we have received
//these will be passed to the bytecode VM to compute
typedef enum
{
  OP_CONSTANT, // A constant will store its opcode and an operand, the operand could be the index of the constant value in memory
  OP_RETURN,
} OpCode;

/* Dynamic array, keep the keep track of the capacity and the count of vals
if the arrays count is < capacity, we can add the item
if not, we create a new array with double the capacity, and copy the elements over to the new location in memory
This is pretty much how slices work in Go
Because we are doubling the size we are not copying the data every time which ensures
Big O of O(1) not O(n) see amortized analysis */

typedef struct
{
  int count;
  int capacity;
  uint8_t *code;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte);
int addConstant(Chunk* chunk, Value value);

#endif
