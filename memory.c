
#include "memory.h"
#include "vm.h"
#include <stdlib.h>

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
  if (newSize == 0) {
    // if we are resizing the array to zero free up the mem space
    free(pointer);
    return NULL;
  }
  // if we are growing the array(or shrinking it greater than 0) we use
  // reallocate which handles reallocation of a pointer to a new memory address
  // it is also equivalent to calling malloc if we are creating a new address
  void *result = realloc(pointer, newSize);
  // if there isn't enough memory realloc returns null
  if (result == NULL)
    exit(1);

  return result;
}

static void freeObject(Obj *object) {
  switch (object->type) {
  case OBJ_CLOSURE: {
    ObjClosure *closure = (ObjClosure *)object;
    FREE_ARRAY(ObjUpvalue *, closure->upvalues, closure->upvalueCount);
    FREE(ObjClosure, object);
    break;
  }
  case OBJ_FUNCTION: {
    ObjFunction *function = (ObjFunction *)object;
    freeChunk(&function->chunk);
    FREE(ObjFunction, object);
    break;
  }
  case OBJ_NATIVE:
    FREE(ObjNative, object);
    break;
  case OBJ_STRING: {
    ObjString *string = (ObjString *)object;
    FREE_ARRAY(char, string->chars, string->length + 1);
    FREE(ObjString, object);
    break;
  }
  case OBJ_UPVALUE:
    FREE(ObjUpvalue, object);
    break;
  }
}

void freeObjects() {
  Obj *object = vm.objects;
  while (object != NULL) {
    Obj *next = object->next;
    freeObject(object);
    object = next;
  }
}
