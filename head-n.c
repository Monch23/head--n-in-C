#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int getlinef(int fd) {
  char sym;
  int rd;

  while ((rd = read(fd, &sym, 1)) > 0 && sym != '\n') {
    printf("%c", sym); // print line's per byte
  }

  putchar(10);

  if (!rd) { // if nothing have to read
    exit(EXIT_SUCCESS);
  }

  return 0;
}

int main(int argc, const char *argv[]) {
  int linesCount = atoi(argv[1]);
  int fd = open(argv[2], O_RDONLY);
  
  if (pread(fd, "l", 1, 0) == 0) {
    perror("file is empty");
    exit(EXIT_FAILURE);
  }

  if (fd < 0) {
    perror("file not found");
    exit(EXIT_FAILURE);
  }

  while (linesCount--) {
    getlinef(fd);
  }

  close(fd);  
  return 0;
}