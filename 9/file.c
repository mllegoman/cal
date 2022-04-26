#include <sys/stat.h>
#include "main.h"

struct getdim {
unsigned int h;
unsigned int w;
};

char *getcfg() {
int i;
char *login, *core;
FILE *F = fopen("../.git/HEAD", "r");;

	if (!F) {
	login = getlogin();
	core = malloc(128);

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
	} else {
	fclose(F);
	core = malloc(96);
	core[0] = '.';
	core[1] = '.';
	core[2] = 47;
	core[3] = 's';
	core[4] = 'e';
	core[5] = 't';
	core[6] = 't';
	core[7] = 'i';
	core[8] = 'n';
	core[9] = 'g';
	core[10] = 's';
	core[11] = 47;
	core[12] = 'c';
	core[13] = 'a';
	core[14] = 'l';
	core[15] = 47;
	core[16] = 0;
	}
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
sesfile[i++] = 111;
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
char *font;
int i, j, end;
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
fseek(F, 0, 2);
end = ftell(F);
fseek(F, 0, 0);
font = malloc(end);
printf("%d\n", end);

i = 0;
tmp = fgetc(F);
	while (i - 1 < end) {
	font[i++] = tmp;
	tmp = fgetc(F);
	}
font[i] = 4;

fclose(F);
return font;

}

void sign(unsigned int date) {
char *datefile = getcfg();
int i = 0;
char *m = (char *)&date;
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
FILE *F = fopen(datefile, "w");
fputc(m[0], F);
fputc(m[1], F);
fputc(m[2], F);
fputc(m[3], F);
fclose(F);
}

char hasText(int date, char cmonth, char realmonth) {
char *datefile = getcfg();
int i = 0;
char dif = cmonth - realmonth + 1;
char isH = dif > 9;
while (datefile[i]) {
i++;
}

if (dif<1) {
return 0;
}

datefile[i++] = dif + 48 + 7*isH;
datefile[i++] = 47;
datefile[i++] = date/10 + 48;
datefile[i++] = date%10 + 48;
datefile[i] = 0;

FILE *F = fopen(datefile, "r");
	if (F) {
		if ((unsigned char)fgetc(F)==255) {
		return 0;
		}
	} else {
	return 0;
	}
return 1;
}
