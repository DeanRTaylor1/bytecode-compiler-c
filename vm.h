#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define FRAMES_MAX 64
#define STACK_MAX (FRAMES_MAX * UINT8_COUNT)

typedef struct {
  ObjClosure *closure;
  uint8_t *ip; // ip -> instruction pointer a reference to the location of the
               // next instruction can also be PC program counbter
  Value *slots;
} CallFrame;

// vm will need to track state but to start with we will create a data structure
// to store all the chunks
typedef struct {
  CallFrame frames[FRAMES_MAX];
  int frameCount;

  Value stack[STACK_MAX];
  Value *stackTop; // store a pointer to the value in front of the top value if
  Table globals;
  Table strings;
  ObjUpvalue* openUpvalues;
  // stack is empty it points to the arr[0]
  Obj *objects; // pointer to head of linked list of objects in memory
} VM;

typedef enum {
  INTERPRET_OK,
  INTERPRET_COMPILE_ERROR,
  INTERPRET_RUNTIME_ERROR
} InterpretResult;

extern VM vm;

void initVM();
void freeVM();
InterpretResult interpret(const char *source);
void push(Value value);
Value pop();

#endif
