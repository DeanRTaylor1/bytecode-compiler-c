#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void repl() {
  char line[1024];
  for (;;) {
    printf("> ");

    if (!fgets(line, sizeof(line), stdin)) {
      printf("\n");
      break;
    }

    interpret(line);
  }
}

static char *readFile(const char *path) {
  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "could not open file \"%s\".\n", path);
    exit(74);
  }

  // fseek find the end of the file
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file); // How many bytes is the file
  rewind(file); // move back to the start of the file after storing the required
                // size

  char *buffer =
      (char *)malloc(fileSize + 1); // allocate enough memory for the file
  if (buffer == NULL) {
    fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
    exit(74);
  }
  size_t bytesRead = fread(buffer, sizeof(char), fileSize,
                           file); // read the file to the buffer
  if (bytesRead < fileSize) {
    fprintf(stderr, "Could not read file \"%s\".\n");
    exit(74);
  }
  buffer[bytesRead] = '\0';
  return buffer;
}

static void runFile(const char *path) {
  char *source = readFile(path);
  InterpretResult result = interpret(source);
  free(source);

  if (result == INTERPRET_COMPILE_ERROR)
    exit(65);
  if (result == INTERPRET_RUNTIME_ERROR)
    exit(70);
}

int main(int argc, const char *argv[]) {
  initVM();

  if (argc == 1) {
    repl();
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    fprintf(stderr, "Usage: clox [path]\n");
  }

  freeVM();
  return 0;
}
