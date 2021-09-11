#include <stdio.h>

int main () {
FILE *F = fopen("default", "r");
FILE *O = fopen("default.1", "a+");
unsigned char c[200];
int i, j;
i = 0;
j = 0;

while (c[i++]!=10) {
c[i] = fgetc(F);
printf("%d\n", c[i]);
}

c[i-2] = 3;

 while (c[j]!=10) {
// printf("%d\n", c[j]);
 fputc(c[j++], O);
 }
}
