#include <stdio.h>

int main (int argc, char *argv[]) {
FILE *F = fopen("default", "a+");
fputc(argv[1][0]-48, F);
fclose(F);
}
