#include <stdio.h>

int main () {
FILE *F = fopen("default", "r");
unsigned char c[4096];
int i = 0;
int j = 0;
c[i] = fgetc(F);
while (1- (c[i]==255)) {
	i++;
	c[i] = fgetc(F);
}
fclose(F);
i--;

FILE *O = fopen("default", "w");

while(1 - (i==j)) {
	fputc(c[j++], F);
}
fclose(O);
}
