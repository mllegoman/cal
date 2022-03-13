#include <stdio.h>
#include <stdlib.h>

int tpow (char m, char n) {
int u = 1;
if (!n) {
return u;
}
while (n) {
u*=m;
n--;
}
return u;
}

int ctoi (char n[7]) {
int s = 1;
int out = 0;
char j = 0;
char i = 0;
if (n[0]=='-') {
n++;
s = -1;
}
while (1-(n[i]==','||n[i]==':')) {
i++;
}
if (n[0]=='0') {
	if (i > 5) {
	return 0;
	}
	j = 2;
	while (j < i) {
	out+=(n[j] - 48) * tpow(16, i - j - 1);
	j++;
	}
} else {
	while (j < i) {
	out+=(n[j] - 48) * tpow(10, i - j - 1);
	j++;
	}
}
return s * out;
}

int main () {
int i, j, k, l, m, sect, ft, dn;
char nchars[7];
char ana;
FILE *F = fopen("contour", "r");
fseek(F, 0, 2);
int len = ftell(F);
fseek(F, 0, 0);
i = 0;
printf("%d\n", len);
return 0;
while (i < len) {
ana = fgetc(F);
j+=(ana==':');
i++;
}

m = j/2;
int secth[m][5];
int *pt[m];
printf("%d\n", m);

i = 0;
j = 0;
k = 0;
l = 0;
fseek(F, 0, 0);
while (i < len) {
ana = fgetc(F);
	if (ana==':') {
	j++;
		if (j&1) {
		k = 0;
		nchars[0] = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		secth[j/2][0] = ctoi(nchars);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		secth[j/2][1] = ctoi(nchars);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		secth[j/2][2] = ctoi(nchars);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		secth[j/2][3] = ctoi(nchars);
		k = 0;
		fgetc(F);
			while (1-(nchars[k-!!k]==':')) {
			nchars[k] = fgetc(F);
			k++;
			}
		secth[j/2][4] = ctoi(nchars);
//		fseek(F, ftell(F)-1, 0);
		} else {
		fgetc(F); // get rid of \n
		fgetc(F);
		i+=2;
		dn = 0;
		ft = 0;
		ana = 0;
			while (!(ana==':')) {
			ana = fgetc(F);
			dn+=(ana=='\n');
			i++;
			ft++;
			}
		pt[l++] = malloc(dn*3*4);
		//sect = ft + i;
		//fseek(F, i, 0);
		// get to end of section naturally
		//fseek(F, sect, 0);
		//printf("scanned section (%d) contains %d lines and %d chars\n", l, dn, ft);
		}
	}
i++;
}
}

