#ifndef clox_object_h
#define clox_object_h

#include "common.h"
#include "value.h"

#define OBJ_TYPE(value) (AS_OBJ(value)->type)

#define IS_STRING(value) isObjType(value, OBJ_STRING)

#define AS_STRING(value) ((ObjString *)AS_OBJ(value))
#define AS_CSTRING(value) (((ObjString *)AS_OBJ(value))->chars)

typedef enum {
  OBJ_STRING,
} ObjType;

struct Obj {
  ObjType type;
  struct Obj *next;
};

// to enable strings to be modified we store the array of chars on the heap. On
// the stack we save the following struct that points to the array head,
// contains the length and the name so that we can use it
// because of the way C creates objects the pointer to an object is also the
// pointer to the first value in the object so the pointer of objstring also
// works as a pointer to obj which is the first defined field
struct ObjString {
  Obj obj;
  int length;
  char *chars;
  uint32_t hash; // we will calculate the hash when the objstring is initialised
                 // as the operation is already o(n) this will save us time
                 // later if we need to store it in our hashtable
};

ObjString *takeString(char *chars, int length);

ObjString *copyString(const char *chars, int length);

void printObject(Value value);

static inline bool isObjType(Value value, ObjType type) {
  return IS_OBJ(value) && AS_OBJ(value)->type == type;
}

#endif
