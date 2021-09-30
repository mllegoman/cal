#include <stdio.h>
#include <sys/stat.h>
#include "file.h"

unsigned int getlastused() {
char *datefile = getcfg();
int i = 0;
char m[4];
unsigned int *ret = (int *)m;
while (datefile[i]) {
i++;
}
datefile[i++] = 108;
datefile[i++] = 97;
datefile[i++] = 115;
datefile[i++] = 116;
datefile[i++] = 117;
datefile[i++] = 115;
datefile[i++] = 101;
datefile[i++] = 100;
datefile[i] = 0;
FILE *F = fopen(datefile, "r");
m[0] = fgetc(F);
m[1] = fgetc(F);
m[2] = fgetc(F);
m[3] = fgetc(F);
fclose(F);
return *ret;
}

void clearcache() { // needs completed
char *monfile = getcfg();
int i = 0

while (monfile[i]) {
i++;
}
monfile[i] = 48;
monfile[i + 1] = 0

	while (1 - (monfile[i]==67)) {
	monfile[i]+=1 + 6*(monfile[i]==58);
	remove(monfile);
	mkdir(monfile, 0700);
	}
}

void backstep(char b) { // re-instate files from (dreg-format.tm_mon) months into the future to their proper positions
char *monfile = getcfg();
int i = 0;

while (monfile[i]) {
i++;
}
monfile[i] = 48;
monfile[i + 1] = 0

}
