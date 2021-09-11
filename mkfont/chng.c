#include <stdio.h>

int main() {
FILE *F = fopen("def", "r");
FILE *O = fopen("out", "a+");
// unsigned char base[50];
unsigned char c;
while (c < 255) {
c = fgetc(F);
	if (c==58) {
	fputc((char)58, O);
	c = 2;
	}
	if (c==16) {
	c = 1;
	}
fputc(c, O);

}

}
