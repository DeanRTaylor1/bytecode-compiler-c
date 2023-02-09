#ifndef clox_value_h
#define clox_value_h

#include "common.h"

typedef double Value;

//In our bytecode compiler, we will store all const literal values in an ValueArray
//This means that when our program needs to find them we just check the offset value to find the value
typedef struct {
  int capacity;
  int count;
  Value* values;
} ValueArray;

//we need the same functionality here to initialise the array and manage
//the space required to store all the values
void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif