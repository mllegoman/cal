#include <ssw.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "file.h"
#include "sbwn.h"

#define uchar unsigned char
#define uint unsigned int

// can do some things here:
 // make some good fonts
 // scale fonts (and basically everything else)


int adjpow(uint n) {
char i = 31;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

uint approxdis(uint x[20], uint y[20], uchar n) {
char i;
uint tot = 0;
uint wh = WH(19);
	for (i = 0; i + 1 < n; i++) {
	tot+=(((x[i]*wh/256)|(x[i+1]*wh/256))<<1)-(x[i]*wh/256)-(x[i+1]*wh/256);
	tot+=(((y[i]*wh/256)|(y[i+1]*wh/256))<<1)-(y[i]*wh/256)-(y[i+1]*wh/256);
	}
return tot;
}

uint approxdis255(uchar *x, uchar *y, uchar n) {
char i;
uint tot = 0;
uint wh = WH(19);
	for (i = 0; i + 1 < n; i++) {
	tot+=(((x[i]*wh/256)|(x[i+1]*wh/256))<<1)-(x[i]*wh/256)-(x[i+1]*wh/256);
	tot+=(((y[i]*wh/256)|(y[i+1]*wh/256))<<1)-(y[i]*wh/256)-(y[i+1]*wh/256);
	}
return tot;
}

uchar dis(char m, char n) {
	if (m - n < n - m) {
	return n - m;
	}
return m - n;
}

void drawcurve(unsigned long rgb, uint *x, uint *y, uchar n) {
uchar i, j;
uint slice[20];
float t, tc, snbl, totx, toty;
tc = (float)1/adjpow(approxdis(x, y, n))/2;
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
		RegionFill((uint)totx, (uint)toty, 1, 1, rgb, 19);
	}
}

void drawstr(uchar *font, uchar str[10], uint x, uint y, uchar dscl) {
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
		RegionFill(x+i*128/dscl+32/dscl, y+32/dscl, 64/dscl, 1, RGB(255, 255, 255), 19);
		RegionFill(x+(i+1)*128/dscl-32/dscl, y+32/dscl, 1, 160/dscl, RGB(255, 255, 255), 19);
		RegionFill(x+    i*128/dscl+32/dscl, y+32/dscl, 1, 160/dscl, RGB(255, 255, 255), 19);
		RegionFill(x+i*128/dscl+32/dscl, y+192/dscl, 64/dscl, 1, RGB(255, 255, 255), 19);
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
			while (1-(j==o)) { // does not know end of file
			cx[pc] = x + i*128/dscl + font[j]/dscl;
			cy[pc++] = y + font[j + 1]/dscl;
			j+=3;
			}
			drawcurve(RGB(255, 255, 255), cx, cy, (o - f)/3);
			}
		}
	i++;
	}
}

int redraw(uchar *font, char nomen[121], int unavail[12], char md[12], char w[12], char cmonth) {
int i, index;

uint x[3];
uint y[3];
uchar n = 3;
char nom[10];
int secsize = WW(19)/9;

index = 0;
i = cmonth * 10;

while (nomen[i]) {
nom[index++] = nomen[i++];
}
nom[index] = 0;

RegionFill(0, 0, WW(19), WH(19), RGB(0, 0, 0), 19);

drawstr(font, nom, WW(19)/2 - index * 128/(500/secsize) / 2, secsize/2, 500/secsize);

	for (i = 0; i < md[cmonth]; i++) {
	index = i + 2*((i + w[cmonth])/7) + 9 + w[cmonth];
	x[0] = (index%9+1)*secsize;
	x[1] = (index%9+1)*secsize;
	x[2] = (index%9+1)*secsize+secsize;
	y[0] = index/9*secsize+secsize;
	y[1] = index/9*secsize;
	y[2] = index/9*secsize;
	drawcurve(RGB(255, 255, 255), x, y, 3);
	}

	for (i = 0; i < 18; i++) {
		if(unavail[i]&&cmonth==unavail[i]>>5) {
		index = unavail[i]&31;
		index = index + 2*((index + 1 + w[cmonth])/7) + 10 + w[cmonth];
		RegionFill(index%9*secsize+1, index/9*secsize+1, secsize-1, secsize-1, RGB(80, 80, 80), 19); // I prefer round swatches over plain squares
		}
	}
return secsize;
}

int main() {
struct cache c;
struct getdim dim = hw(1);
char *font = getfont("default", 8);
clock_t ctime;
pthread_t thread[19];
char info[19][3];
int  unavail[19];  // list of dates taken by each thread
int secsize;
int date;
time_t t = time(NULL);
struct tm time = *localtime(&t);
char cmonth = time.tm_mon;
int       i;
char md[12];
char  w[12];

char nomen[121] = 
"January\0\0\0February\0\0March\0\0\0\0\0April\0\0\0\0\0May\0\0\0\0\0\0\0June\0\0\0\0\0\0July\0\0\0\0\0\0August\0\0\0\0September\0October\0\0\0November\0\0December\0\0"; 

md[0]  = 31;
md[1]  = 28+!(time.tm_year%4);
md[2]  = 31;
md[3]  = 30;
md[4]  = 31;
md[5]  = 30;
md[6]  = 31;
md[7]  = 31;
md[8]  = 30;
md[9]  = 31;
md[10] = 30;
md[11] = 31;

for (i = 0; i < 18; i++) {
unavail[i] = 0;
}

for (i = 0; i < 18; i++) {
info[i][0] = i;
info[i][1] = 0;
info[i][2] = 0;
}

w[0]  = (371-time.tm_yday+time.tm_wday)%7;
for (i = 0; (i + 1) < 11; i++) {
w[i+1]  = (w[i]+md[i])%7;
}

int cthread, backlog, index;
backlog = 0;


XI_();
XI(0, "", "", dim.w, dim.h, 0, 0, 19);
Eve(&c, 19);
RegionFill(0, 0, dim.w, dim.h, RGB(0, 0, 0), 19);
secsize = redraw(font, nomen, unavail, md, w, cmonth);

	while(1) {
		while(Pend(19)) { 
		Eve(&c, 19);
			if (c.t==3) {
			secsize = redraw(font, nomen, unavail, md, w, cmonth);
			}
			if (c.t==2) {
				if (c.x<secsize&&cmonth!=0) {
				// ctime = clock() - ctime; draw lines relative to c.y
				cmonth--;
				redraw(font, nomen, unavail, md, w, cmonth);
				}

				if (c.x>secsize*8&&cmonth!=11) {
				
				cmonth++;
				redraw(font, nomen, unavail, md, w, cmonth);
				}

				if (c.x<secsize*8&&c.x>secsize) {
				index = (c.y/secsize*9)+c.x/secsize;
				date = index - (2*(index/9) + 1 + w[cmonth]) - 7;
					if (!(date<0)&&!(date>md[cmonth]-1)) {
					date+=cmonth<<5;
					i = 0;
					while (date!=unavail[i]&&i<19) {
					i++;
					}
						if (i==19) {
						cthread = 0;
							while (info[cthread][1]) {
							cthread++;
							}
							if (cthread==19) {
							info[backlog][2] = 1;
							unavail[backlog] = date;
							redraw(font, nomen, unavail, md, w, cmonth);
							hauldata(backlog, date, 1);
							hauldata(backlog, date, 0);
							info[backlog][2] = 0;
							backlog = backlog % 19 + 1;
							}
							if (cthread<19) {
							backlog = 0;
							info[cthread][1] = 1;
							unavail[cthread] = date;
							redraw(font, nomen, unavail, md, w, cmonth);
							hauldata(cthread, date, 0);
							pthread_create(&thread[cthread], NULL, subwin, &info[cthread]);
							}
						}
						if (i<19) {
						info[i][1] = 0;
						unavail[i] = 0;
						redraw(font, nomen, unavail, md, w, cmonth);
						pthread_join(thread[i], NULL);
						hauldata(i, date, 1);
						}
					}
				}
			}
			if (c.t==1) {
				if (c.txt[0]=='q') {
				setdim(WH(19), WW(19), 1);
				Clean(19);
				XX(0);
				}
			}
		}
	}
}


/*
Member  Type    Meaning Range
tm_sec  int     seconds after the minute        0-61*
tm_min  int     minutes after the hour  0-59
tm_hour int     hours since midnight    0-23
tm_mday int     day of the month        1-31
tm_mon  int     months since January    0-11
tm_year int     years since 1900
tm_wday int     days since Sunday       0-6
tm_yday int     days since January 1    0-365
tm_isdst        int     Daylight Saving Time flag

*/
