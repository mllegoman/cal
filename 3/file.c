#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct getdim {
unsigned int h;
unsigned int w;
};

char *getcfg() {
int i, j;
char *login = getlogin();
char *core = malloc(64);
login = getlogin();

for (i = 0; i < 31; i++) {
core[i] = login[i];
}

i = 0;

while (login[i]) {
i++;
}

for (j = i; j; j--) {
core[j + 6] = core[j];
}

core[0] = "/"; // /home/
core[1] = "h";
core[2] = "o";
core[3] = "m";
core[4] = "e";
core[5] = "/";

i+=6;

core[i++] = "/"; // /.config/cal/
core[i++] = ".";
core[i++] = "c";
core[i++] = "o";
core[i++] = "n";
core[i++] = "f";
core[i++] = "i";
core[i++] = "g";
core[i++] = "/";
core[i++] = "c";
core[i++] = "a";
core[i++] = "l";
core[i++] = "/";
core[i] = 0;

return core;
}

struct getdim hw(char win) {
struct getdim ret;
char i;
char *dimfile = getcfg();

while (dimfile[i]) {
i++;
}
dimfile[i++] = "d"; // dim.win_\0";
dimfile[i++] = "i";
dimfile[i++] = "m";
dimfile[i++] = ".";
dimfile[i++] = "w";
dimfile[i++] = "i";
dimfile[i++] = "n";
dimfile[i++] = 48 + win;
dimfile[i] = 0;

FILE *dim = fopen(dimfile, "r");
char rh[4];
char rw[4];
rh[3] = fgetc(dim);
rh[2] = fgetc(dim);
rh[1] = fgetc(dim);
rh[0] = fgetc(dim);
rw[3] = fgetc(dim);
rw[2] = fgetc(dim);
rw[1] = fgetc(dim);
rw[0] = fgetc(dim);
ret.h = *(unsigned int *)rh;
ret.w = *(unsigned int *)rw;
fclose(dim);

return ret;
}

void setdim(unsigned int h, unsigned int w, char win) {
char i;
char *dimfile = getcfg();

while (dimfile[i]) {
i++;
}
dimfile[i++] = "d"; // dim.win_\0";
dimfile[i++] = "i";
dimfile[i++] = "m";
dimfile[i++] = ".";
dimfile[i++] = "w";
dimfile[i++] = "i";
dimfile[i++] = "n";
dimfile[i++] = 48 + win;
dimfile[i] = 0;

FILE *dim = fopen(dimfile, "w");

fputc(*((char *)&h+3), dim);
fputc(*((char *)&h+2), dim);
fputc(*((char *)&h+1), dim);
fputc((char)h, dim);
fputc(*((char *)&w+3), dim);
fputc(*((char *)&w+2), dim);
fputc(*((char *)&w+1), dim);
fputc((char)w, dim);
fclose(dim);
}

FILE *opensessionfile(char sesid) {
char i;
char *sesfile = getcfg();

while (sesfile[i]) {
i++;
}

sesfile[i++] = "."; // .session__\0";
sesfile[i++] = "s";
sesfile[i++] = "e";
sesfile[i++] = "s";
sesfile[i++] = "s";
sesfile[i++] = "i";
sesfile[i++] = "o";
sesfile[i++] = "n";
sesfile[i++] = 48 + sesid/10;
sesfile[i++] = 48 + sesid%10;
sesfile[i] = 0;

FILE *F = fopen(sesfile, "a+");

return F;
}

void hauldata(char sesid, int date, char p) {
char i, j;
char *sesfile   = getcfg();
// .session__\0;
char *permafile = getcfg();
// _/__\0;

while (sesfile[i]) {
i++;
}

sesfile[i++] = "."; // .session__\0";
sesfile[i++] = "s";
sesfile[i++] = "e";
sesfile[i++] = "s";
sesfile[i++] = "s";
sesfile[i++] = "i";
sesfile[i++] = "o";
sesfile[i++] = "n";
sesfile[i++] = 48 + sesid/10;
sesfile[i++] = 48 + sesid%10;
sesfile[i] = 0;

while (permafile[j]) {
j++;
}

permafile[j++] = 48 + (date>>5);
permafile[j++] = "/";
permafile[j++] = 48 + (date&31)/10%10;
permafile[j++] = 48 + (date&31)%10;
permafile[j] = 0;

	if (p) {
	rename(sesfile, permafile);
	} else {
	rename(permafile, sesfile);
	}
}

void funnel(char sesid, char base[]) {
char i;
char *sesfile = getcfg();

while (sesfile[i]) {
i++;
}

sesfile[i++] = "."; // .session__\0";
sesfile[i++] = "s";
sesfile[i++] = "e";
sesfile[i++] = "s";
sesfile[i++] = "s";
sesfile[i++] = "i";
sesfile[i++] = "o";
sesfile[i++] = "n";
sesfile[i++] = 48 + sesid/10;
sesfile[i++] = 48 + sesid%10;
sesfile[i] = 0;

FILE *F = fopen(sesfile, "r");
printf("%u\n", F);
if (F) {
/*
opt = 0;
fseek(F, 0, 2);
base[opt++] = fgetc(F);
fseek(F, ftell(F)-2, 0);
	
	while(base[opt]!=(char)234||ftell(F)-2<0) {
	base[opt++] = fgetc(F);
	fseek(F, ftell(F)-2, 0);
	}
off = opt;
	while(opt > 0) {
	base[off++] = base[opt--];
	}
base[off] = 0;
off/=2;
opt = 0;
	while(base[off - 1]!=0) {
	base[opt++] = base[off++];
	}
printf("%s\n", base);*/
fclose(F);
}
}
