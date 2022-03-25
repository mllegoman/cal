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

int ctoi (char n[10]) {
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
int i, j, k, l, m, n, ln;
char nchars[10];
char ana;
FILE *F = fopen("contour", "r");
fseek(F, 0, 2);
int len = ftell(F);
fseek(F, 0, 0);
i = 0;
j = 0;
while (i < len) {
ana = fgetc(F);
j+=(ana==':');
i++;
}

if (j==0||j&1) {
return 1;
}

m = j/2;
int secth[m][6];
int *pt[m];

i = 0;
j = 0;
k = 0;
l = 0;
fseek(F, 0, 0);
while (1) {
ana = fgetc(F);
i++;
	while (1-(ana==':')&&i < len) {
	ana = fgetc(F);
	i++;
	}
	if (i>len - 1) {
	break;
	}
		k = 0;
		nchars[0] = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j][0] = ctoi(nchars);
		//printf("0 %d\n", i);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j][1] = ctoi(nchars);
		//printf("1 %d\n", i);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j][2] = ctoi(nchars);
		//printf("2 %d\n", i);
		k = 0;
			while (1-(nchars[k-!!k]==',')) {
			nchars[k] = fgetc(F);
			k++;
			}
		i+=k;
		secth[j][3] = ctoi(nchars);
		//printf("3 %d %d\n", i, secth[j][3]);
		k = 0;
		fgetc(F);
		i++;
			while (1-(nchars[k-!!k]==':')) {
			nchars[k] = fgetc(F);
			k++;
			//printf("%d %c", k, 10*(k%30==0));
			}
		i+=k;
		//printf("let me guess\n");
		secth[j][4] = ctoi(nchars);
		//printf("4 %d\n", i);
		//printf("%d %d %d %d %d at %d\n", secth[j][0], secth[j][1], secth[j][2], secth[j][3], secth[j][4], j);
		ana = fgetc(F);
		i++;
			while (1-(ana>47&&ana<58)) {
			ana = fgetc(F);
			i++;
			}
		n = ftell(F) - 1;
			ln = 0;
			while (ana!=':'&&i < len) {
			ana = fgetc(F);
			ln+=ana=='\n';
			i++;
			}
		secth[j][5] = ln;


		pt[j] = malloc(ln*4*3);


		fseek(F, n, 0);
		i = n;
		n = 0;
			while (n < ln) {
			nchars[0] = fgetc(F);
			nchars[1] = fgetc(F);
			i+=2;
			pt[j][n*3] = ctoi(nchars);
				if (pt[j][n*3]&&pt[j][n*3-3*!!n]) {
				pt[j][n*3-3*!!n] = 0;
				}
			k = 0;
				while (1-(nchars[k-!!k]==',')) {
				nchars[k] = fgetc(F);
				k++;
				i++;
				}
			pt[j][n*3+1] = ctoi(nchars);
			k = 0;
				while (1-(nchars[k-!!k]=='\n')&&i < len) {
				nchars[k] = fgetc(F);
				k++;
				i++;
				}
			nchars[k-1] = ',';
			pt[j][n*3+2] = ctoi(nchars);
			//printf("%d %d %d at %d in %d\n", pt[j][n*3], pt[j][n*3+1], pt[j][n*3+2], n, ln);
			n++;
			}
	j++;
}
fclose(F);

//printf("here\n");

F = fopen("../../settings/cal/fonts/default.red", "w");
for (i = 0; i < m; i++) {
	if (secth[i][4] < 128) {
	fprintf(F, "%c%c%c", secth[i][4], ':', 2);
		for (j = 0; j < secth[i][5]; j++) {
		pt[i][j*3+1]-=secth[i][0];
		pt[i][j*3+2]-=secth[i][1];
		pt[i][j*3+1]*=128;
		pt[i][j*3+2]*=255;
		pt[i][j*3+1]/=(secth[i][2]-secth[i][0]);
		pt[i][j*3+2]/=(secth[i][3]-secth[i][1]);
		pt[i][j*3+2] = 255 - pt[i][j*3+2];
		fprintf(F, "%c%c%c", (unsigned char)pt[i][j*3+1], (unsigned char)pt[i][j*3+2], (unsigned char)(pt[i][j*3] + 2*(i==m-1&&j==secth[i][5]-1)));
		//printf("%d %c", pt[i][j*3], 10*(j%10==0));
		}
	}
}

fclose(F);
return 0;
}

