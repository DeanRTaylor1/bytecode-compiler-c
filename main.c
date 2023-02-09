#include "chunk.h"
#include "common.h"
#include "debug.h"


int main(int arg, const char* argv[]) {
  Chunk chunk;
  initChunk(&chunk);
  
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);

  writeChunk(&chunk, OP_RETURN);

  disassembleChunk(&chunk, "text chunk");
  freeChunk(&chunk);
  return 0;
}
