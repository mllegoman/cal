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
		if (n[j] > 90) {
		out+=(n[j] - 86) * tpow(16, i - j - 1);
		} else {
		out+=(n[j] - 48) * tpow(16, i - j - 1);
		}
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

while (i < len) {
ana = fgetc(F);
j+=(ana==':');
i++;
}

m = j/2;
int secth[m][5];
int *pt[m];

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
		i+=k;
		secth[j/2][0] = ctoi(nchars);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j/2][1] = ctoi(nchars);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j/2][2] = ctoi(nchars);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j/2][3] = ctoi(nchars);
		k = 0;
		fgetc(F);
			while (1-(nchars[k-!!k]==':')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j/2][4] = ctoi(nchars);
		fseek(F, ftell(F)-1, 0);
		i--;
		} else {
		fgetc(F); // get rid of \n
		i++;
		dn = 0;
		ft = 0;
		ana = 0;
			while (!(ana==':')&&i < len) {
			ana = fgetc(F);
			dn+=(ana=='\n');
			ft++;
			i++;
			}
		int big[dn*3];
		pt[l++] = big;
		fseek(F, i - ft + 1, 0);
		//fseek(F, i, 0);
		sect = 0;
			while (sect < dn) {
			nchars[0] = 0;
			k = 0;
				while (1-(nchars[k-!!k]==',')) { // dont need while
				nchars[k] = fgetc(F);
				k++;
				printf("%c\n", nchars[k-!!k]);
				}
			pt[j/2][sect*3] = ctoi(nchars);
			return 0;
			printf("%d\n", pt[j/2][sect*3]);
				if (pt[j-!!j][0]&pt[j][0]) {
				pt[j-!!j][0] = 0;
				}
			nchars[0] = 0;
			k = 0;
				while (1-(nchars[k-!!k]==',')) {
				nchars[k] = fgetc(F);
				k++;
				}
			pt[j/2][sect*3+1] = ctoi(nchars);
			k = 0;
				while (1-(nchars[k-!!k]=='\n')) {
				nchars[k] = fgetc(F);
				k++;
				}
			pt[j/2][sect*3+2] = ctoi(nchars);
			sect++;
			}
		//fseek(F, ftell(F)-1, 0);
		i--;
		}
	}
i++;
}
}

