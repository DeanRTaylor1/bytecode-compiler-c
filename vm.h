#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

//vm will need to track state but to start with we will create a data structure
//to store all the chunks
typedef struct {
  Chunk* chunk;
  uint8_t* ip; //ip -> instruction pointer a reference to the location of the next instruction can also be PC program counbter
  Value stack[STACK_MAX];
  Value* stackTop; //store a pointer to the value in front of the top value if stack is empty it points to the arr[0]
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif
