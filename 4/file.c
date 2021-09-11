#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct getdim {
unsigned int h;
unsigned int w;
};

char *getcfg() {
int i;
char *login = getlogin();
char *core = malloc(128);

for (i = 0; i < 31; i++) {
core[i] = login[i];
}

for (i = 0; login[i]; i++) {
core[i + 6] = login[i];
}

core[0] = 47; // /home/
core[1] = 104;
core[2] = 111;
core[3] = 109;
core[4] = 101;
core[5] = 47;

i+=6;

core[i++] = 47; // /.config/cal/
core[i++] = 46;
core[i++] = 99;
core[i++] = 111;
core[i++] = 110;
core[i++] = 102;
core[i++] = 105;
core[i++] = 103;
core[i++] = 47;
core[i++] = 99;
core[i++] = 97;
core[i++] = 108;
core[i++] = 47;
core[i] = 0;

return core;
}

struct getdim hw(char win) {
struct getdim ret;
char i = 0;
char *dimfile = getcfg();

while (dimfile[i]) {
i++;
}
dimfile[i++] = 100; // dim.win_\0";
dimfile[i++] = 105;
dimfile[i++] = 109;
dimfile[i++] = 46;
dimfile[i++] = 119;
dimfile[i++] = 105;
dimfile[i++] = 110;
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
char i = 0;
char *dimfile = getcfg();

while (dimfile[i]) {
i++;
}
dimfile[i++] = 100; // dim.win_\0";
dimfile[i++] = 105;
dimfile[i++] = 109;
dimfile[i++] = 46;
dimfile[i++] = 119;
dimfile[i++] = 105;
dimfile[i++] = 110;
dimfile[i++] = 48 + win;
dimfile[i] = 0;

FILE *dim = fopen(dimfile, "w");

char *rh = (char *)&h;
char *rw = (char *)&w;

fputc(rh[3], dim);
fputc(rh[2], dim);
fputc(rh[1], dim);
fputc(rh[0], dim);
fputc(rw[3], dim);
fputc(rw[2], dim);
fputc(rw[1], dim);
fputc(rw[0], dim);
fclose(dim);
}

FILE *opensessionfile(char sesid) {
char i = 0;
char *sesfile = getcfg();

while (sesfile[i]) {
i++;
}

sesfile[i++] = 46; // .session__\0";
sesfile[i++] = 115;
sesfile[i++] = 101;
sesfile[i++] = 115;
sesfile[i++] = 115;
sesfile[i++] = 105;
sesfile[i++] = 11;
sesfile[i++] = 110;
sesfile[i++] = 48 + sesid/10;
sesfile[i++] = 48 + sesid%10;
sesfile[i] = 0;

FILE *F = fopen(sesfile, "a+");

return F;
}

void hauldata(char sesid, int date, char p) {
char i, j;
char *sesfile   = getcfg();
char *permafile = getcfg();

i = 0;
j = 0;

while (sesfile[i]) {
i++;
}

sesfile[i++] = 46; // .session__\0";
sesfile[i++] = 115;
sesfile[i++] = 101;
sesfile[i++] = 115;
sesfile[i++] = 115;
sesfile[i++] = 105;
sesfile[i++] = 111;
sesfile[i++] = 110;
sesfile[i++] = 48 + sesid/10;
sesfile[i++] = 48 + sesid%10;
sesfile[i] = 0;

while (permafile[j]) {
j++;
}

permafile[j++] = 48 + (date>>5); // _/__
permafile[j++] = 47;
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
char i = 0;
char *sesfile = getcfg();

while (sesfile[i]) {
i++;
}

sesfile[i++] = 46; // .session__\0";
sesfile[i++] = 115;
sesfile[i++] = 101;
sesfile[i++] = 115;
sesfile[i++] = 115;
sesfile[i++] = 105;
sesfile[i++] = 111;
sesfile[i++] = 110;
sesfile[i++] = 48 + sesid/10;
sesfile[i++] = 48 + sesid%10;
sesfile[i] = 0;

FILE *F = fopen(sesfile, "r");

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

char *getfont(char *fontn, char n){
char *legure = getcfg();
char *font = malloc(4096);
int i, j;
unsigned char tmp;
i = 0;
j = 0;

while(legure[i]){
i++;
}

legure[i++] = 102;
legure[i++] = 111;
legure[i++] = 110;
legure[i++] = 116;
legure[i++] = 115;
legure[i++] = 47;
	while (j < n) {
	legure[i++] = fontn[j++];
	}
legure[i] = 0;

FILE *F = fopen(legure, "r");

i = 0;
tmp = fgetc(F);
	while (tmp < 255) {
	font[i++] = tmp;
	tmp = fgetc(F);
	}
font[i] = 4;

fclose(F);
return font;

}
