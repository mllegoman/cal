#include <stdio.h>

int main () {
FILE *F = fopen("default", "r");
unsigned char c[3];
c[2] = 0;
	while (c[2] < 255) {
	c[0] = fgetc(F);
	c[1] = fgetc(F);
	c[2] = fgetc(F);
		if (c[2]==3) {
		printf("\\e");
		}
		if (c[2]==2){
		printf("%c%c", c[0], c[1]);
		}
		if (c[2]==1) {
		printf("[%d,%d]", c[0], c[1]);
		printf("\\c");
		}
		if (c[2]==0) {
		printf("[%d,%d]", c[0], c[1]);
		}
	}
printf("\n");
}
