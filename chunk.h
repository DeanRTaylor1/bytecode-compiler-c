#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

// The expression a != b has the same semantics as !(a == b), so the compiler is
// free to compile the former as if it were the latter. Instead of a dedicated
// OP_NOT_EQUAL instruction, it can output an OP_EQUAL followed by an OP_NOT.
// Likewise, a <= b is the same as !(a > b) and a >= b is !(a < b). Thus, we
// only need three new instructions.

// These are the types of the chunks we have received
// these will be passed to the bytecode VM to compute
typedef enum {
  OP_CONSTANT, // A constant will store its opcode and an operand, the operand
               // could be the index of the constant value in memory
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_POP,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_GET_GLOBAL,
  OP_DEFINE_GLOBAL,
  OP_SET_GLOBAL,
  OP_GET_UPVALUE,
  OP_SET_UPVALUE,
  OP_GET_PROPERTY,
  OP_SET_PROPERTY,
  OP_GET_SUPER,
  OP_EQUAL,
  OP_GREATER,
  OP_LESS,
  OP_ADD,
  OP_SUBTRACT,
  OP_MULTIPLY,
  OP_DIVIDE,
  OP_NOT,
  OP_NEGATE,
  OP_PRINT,
  OP_JUMP,
  OP_JUMP_IF_FALSE,
  OP_LOOP,
  OP_CALL,
  OP_INVOKE,
  OP_SUPER_INVOKE,
  OP_CLOSURE,
  OP_CLOSE_UPVALUE,
  OP_RETURN,
  OP_CLASS,
  OP_INHERIT,
  OP_METHOD
} OpCode;
/* Dynamic array, keep the keep track of the capacity and the count of vals
if the arrays count is < capacity, we can add the item
if not, we create a new array with double the capacity, and copy the elements
over to the new location in memory This is pretty much how slices work in Go
Because we are doubling the size we are not copying the data every time which
ensures Big O of O(1) not O(n) see amortized analysis */

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  int *lines; // we will keep a separate array of line numbers to report errors
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);
void freeChunk(Chunk *chunk);
void writeChunk(Chunk *chunk, uint8_t byte,
                int line); // we must pass the line number of the chunk
int addConstant(Chunk *chunk, Value value);

#endif
