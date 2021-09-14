#include <ssw.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint unsigned int

float cosine(float x) {
return 1 - x*x/2 + x*x*x*x/24 - x*x*x*x*x*x/720 + x*x*x*x*x*x*x*x/40320;
}

float sine(float x) {
return x - x*x*x/6 + x*x*x*x*x/120 - x*x*x*x*x*x*x/5040;
}

void *rotate(void *ptr, void *ptr1, float angle, char type) {
	if (type) {
	uint *out = malloc(8);
	uint *o = ptr;
	uint *r = ptr1;
	out[0] = cosine(angle)*(r[0] - o[0]) - sine(angle)*(r[1] - o[1])+o[0];
	out[1] = sine(angle)*(r[0] - o[0]) + cosine(angle)*(r[1] - o[1])+o[1];
	return (void *)out;
	} else {
	uchar *out = malloc(2);
	uchar *o = ptr;
	uchar *r = ptr1;
	out[0] = cosine(angle)*(r[0] - o[0]) - sine(angle)*(r[1] - o[1])+o[0];
	out[1] = sine(angle)*(r[0] - o[0]) + cosine(angle)*(r[1] - o[1])+o[1];
	return (void *)out;
	}
}

uchar *italicize(char *font) {
int i = 0;
uchar origin[2];
uchar *xy;
origin[0] = 0;
origin[1] = 0;
uchar *out = malloc(4096);
	while (1 - (font[i - !!i]==3)) {
		if (font[i + 2]==2) {
		out[i] = font[i];
		i++;
		out[i] = font[i];
		i++;
		out[i] = 2;
		i++;
		} else {
		xy = (char *)rotate((void *)origin, (void *)(font + i * 3), 0, 0);
		out[i] = xy[0];
		i++;
		out[i] = xy[1] - 8;
		i++;
		out[i] = font[i];
		i++;
		}
	}
return out;
}

int adjpow(uint n) {
char i = 31;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

uint approxdis(uint x[20], uint y[20], uchar n, char win) {
char i;
uint tot = 0;
uint wh = WH(win);
	for (i = 0; i + 1 < n; i++) {
	tot+=(((x[i]*wh/256)|(x[i+1]*wh/256))<<1)-(x[i]*wh/256)-(x[i+1]*wh/256);
	tot+=(((y[i]*wh/256)|(y[i+1]*wh/256))<<1)-(y[i]*wh/256)-(y[i+1]*wh/256);
	}
return tot;
}

void drawcurve(unsigned long rgb, uint *x, uint *y, uchar n, char win) {
uchar i, j;
uint slice[20];
float t, tc, snbl, totx, toty;
tc = (float)1/adjpow(approxdis(x, y, n, win))/2;
snbl = 1;

slice[0] = 1;
	for (i = 1; i < (n + 1)/2; i++) {
	slice[i] = slice[i - 1] * (n - i)/i;
	}

	for (i = n - 1; i > (n - 1)/2; i--) {
	slice[i] = slice[n - i - 1];
	}

	for (t = 0; (uint)t==0; t+=tc+tc*(t>0.25||t>0.75)) {
		totx=0;
		toty=0;
		i  = 0;
		while (i < n) { // n-1 times (for each term)
		snbl = 1;
			for (j = 0; j < n - i - 1; j++) {
			snbl*=(1 - t);
			}
			for (j = 0; j < i; j++) {
			snbl*=t;
			}

		snbl*=slice[i];

		totx+=x[i]*snbl;
		toty+=y[i]*snbl;
		i++;
		}
		RegionFill((uint)totx, (uint)toty, 1, 1, rgb, win);
	}
}

void drawstr(uchar *font, uchar str[10], uint x, uint y, uchar dscl, char win) {
uint i, j, f, o;
char size, pc;

i = 0;
	while (str[i]) {
	//printf("%c\n", str[i]);
	j = 0;
		while (font[j-!!j]!=3) {
			if (str[i]==font[j]&&font[j+2]==2) {
			j+=3;
			break;
			}
		j+=3;
		}
		if (font[j-1]==3) {
		RegionFill(x+i*128/dscl+32/dscl, y+32/dscl, 64/dscl, 1, RGB(255, 255, 255), win);
		RegionFill(x+(i+1)*128/dscl-32/dscl, y+32/dscl, 1, 160/dscl, RGB(255, 255, 255), win);
		RegionFill(x+    i*128/dscl+32/dscl, y+32/dscl, 1, 160/dscl, RGB(255, 255, 255), win);
		RegionFill(x+i*128/dscl+32/dscl, y+192/dscl, 64/dscl, 1, RGB(255, 255, 255), win);
		} else {
		o = j + 3;
			while (1 - (font[o-1]==3||font[o+2]==2)) {
			o = j + 3;
				while (font[o-1]!=1&&font[o-1]!=3&&font[o+2]!=2) {
				o+=3;
				}
			uint cx[(o - j)/3];
			uint cy[(o - j)/3];
			pc = 0;
			f = j;
			while (1-(j==o)) {
			cx[pc] = x + i*128/dscl + font[j]/dscl;
			cy[pc++] = y + font[j + 1]/dscl;
			j+=3;
			}
			drawcurve(RGB(255, 255, 255), cx, cy, (o - f)/3, win);
			}
		}
	i++;
	}
}
