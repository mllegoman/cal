#include <stdio.h>

int main () {
FILE *F = fopen("/home/widower/.config/cal/dim.win1", "r");
for (int i = 0; i < 8; i++) {
printf("%d\n", fgetc(F));
}
}
