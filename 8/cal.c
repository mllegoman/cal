/*
TODO:
write file handling functions for relativising the cache

animations!
 * save x/y coordinates of clicks on date-sections (draw reactions to clicks in redraw)
 * handle animations in a separate thread

backdrops?

finish up the client to work on the daemon (cald)

make a more permanant solution to drawing unavail[]

restrict modifyable dates
*/

#include <ssw.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "file.h"
#include "bezier.h"
#include "sbwn.h"

#define uchar unsigned char
#define uint unsigned int

const char nomen[121] = 
"January\0\0\0February\0\0March\0\0\0\0\0April\0\0\0\0\0May\0\0\0\0\0\0\0June\0\0\0\0\0\0July\0\0\0\0\0\0August\0\0\0\0September\0October\0\0\0November\0\0December\0\0"; 
const char clature[71] = "Sunday\0\0\0\0Monday\0\0\0\0Tuesday\0\0\0Wednesday\0Thursday\0\0Friday\0\0\0\0Saturday\0\0";

int redraw(uchar *font, int unavail[12], char cmonth, char w[24], char md[24], struct tm format) {
int i, j, index;

uint x[4];
uint y[4];
uchar n = 3;
char nom[10];
int secsize = WW(19)/9;

index = 0;
i = cmonth%12 * 10;

while (nomen[i]) {
nom[index++] = nomen[i++];
}
nom[index] = 0;

RegionFill(0, 0, WW(19), WH(19), RGB(0, 0, 0), 19);

drawstr(font, nom, WW(19)/2 - index * 128/(500/secsize) / 2, secsize/3, 500/secsize, 19);

	for (i = 0; i < md[cmonth]; i++) {
	index = i + 2*((i + w[cmonth])/7) + 9 + w[cmonth];
	x[0] = (index%9+1)*secsize;
	x[1] = (index%9+1)*secsize;
	x[2] = (index%9+1)*secsize+secsize/3;
	y[0] = index/9*secsize+secsize/3;
	y[1] = index/9*secsize;
	y[2] = index/9*secsize;
	drawcurve(RGB(255, 255, 255), x, y, 3, 3, secsize, 19);
	x[0]+=secsize;
	x[1]+=secsize;
	x[2]+=secsize/3;
	drawcurve(RGB(255, 255, 255), x, y, 3, 1, secsize, 19);
	y[0]+=secsize/3;
	y[1]+=secsize;
	y[2]+=secsize;
	drawcurve(RGB(255, 255, 255), x, y, 3, 1, secsize, 19);
	x[0]-=secsize;
	x[1]-=secsize;
	x[2]-=secsize/3;
	drawcurve(RGB(255, 255, 255), x, y, 3, 3, secsize, 19);
		if (i/9) {
		uchar txt[3];
		txt[0] = (i+1)/10 + 48;
		txt[1] = (i+1)%10 + 48;
		txt[2] = 0;
		drawstr(font, txt, (index%9+1)*secsize + secsize/5, index/9*secsize + secsize/5, 1000/secsize, 19);
		} else {
		uchar txt[2];
		txt[0] = i + 48 + 1;
		txt[1] = 0;
		drawstr(font, txt, (index%9+1)*secsize + secsize/5, index/9*secsize + secsize/5, 1000/secsize, 19);
		}
		x[0] = (index%9+1)*secsize + secsize*14/21;
		x[1] = x[0];
		x[2] = x[0] + secsize*3/21;
		x[3] = x[2];
		y[0] = index/9*secsize + secsize*14/21;
		y[1] = y[0] + secsize*3/21;
		y[2] = y[1];
		y[3] = y[0] + 1;
		if (cmonth==format.tm_mon&&i+1==format.tm_mday) {
		drawcurve(RGB(0, 255, 255), x, y, 4, 0, secsize/2, 19);
		x[0]-=secsize*5/21;
		x[1]=x[0];
		x[2]-=secsize*5/21;
		x[3]=x[2];
		}
		if (hasText(i, cmonth, (char)format.tm_mon)) {
		drawcurve(RGB(80, 255, 40), x, y, 4, 0, secsize/2, 19);
		x[0]-=secsize*5/21;
		x[1]=x[0];
		x[2]-=secsize*5/21;
		x[3]=x[2];
		}
		for (j = 0; j < 18; j++) {
			if (cmonth-format.tm_mon+1==unavail[j]>>5&&(unavail[j]&31)==i&&1-(cmonth<format.tm_mon)) {
			drawcurve(RGB(255, 100, 0), x, y, 4, 0, secsize/2, 19);
			}
		}
	}
return secsize;
}

int main() {
struct cache c;
struct getdim dim = hw(1);
char *font = getfont("default.red", 12);
char *italic = 0; // italicize(font);
clock_t ctime;
pthread_t thread[19];
char info[19][3];
int  unavail[19];  // list of dates taken by each thread
uint dreg;
int secsize;
int date;
int i;

// start time constants
time_t realtime = time(NULL);
struct tm format = *localtime(&realtime);
char cmonth = format.tm_mon;
char md[24];
char  w[24];

md[0]  = 31;
md[1]  = 28+!(format.tm_year%4);
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

md[12] = 31;
md[13] = 28+!((format.tm_year+1)%4);
md[14] = 31;
md[15] = 30;
md[16] = 31;
md[17] = 30;
md[18] = 31;
md[19] = 31;
md[20] = 30;
md[21] = 31;
md[22] = 30;
md[23] = 31;

w[0]  = (371-format.tm_yday+format.tm_wday)%7;
for (i = 0; (i + 1) < 23; i++) {
w[i+1]  = (w[i]+md[i])%7;
} 
// end time constants

for (i = 0; i < 18; i++) {
unavail[i] = 0;
}

for (i = 0; i < 18; i++) {
info[i][0] = i;
info[i][1] = 0;
info[i][2] = 0;
}

int cthread, backlog, index;
backlog = 0;

XI_();
XI(0, "", "", dim.w, dim.h, 0, 0, 19);
Eve(&c, 19);
RegionFill(0, 0, dim.w, dim.h, RGB(0, 0, 0), 19);
secsize = redraw(font, unavail, cmonth, w, md, format);

	while(1) {
		while(Pend(19)) { 
		Eve(&c, 19);
			if (c.t==3) {
			secsize = redraw(font, unavail, cmonth, w, md, format);
			}
			if (c.t==2) {
				if (c.x<secsize&&cmonth) {
				cmonth--;
				redraw(font, unavail, cmonth, w, md, format);
				}

				if (c.x>secsize*8&&cmonth!=format.tm_mon+11) {
				
				cmonth++;
				redraw(font, unavail, cmonth, w, md, format);
				}
			index = (c.y/secsize*9)+c.x/secsize;
			date = index - (2*(index/9) + 8 + w[cmonth]);
				if (c.x<secsize*8&&c.x>secsize&&1-(cmonth<format.tm_mon)&&2-(date+1<format.tm_mday)-(cmonth==format.tm_mon)) {
					if (!(date<0)&&!(date>md[cmonth]-1)) {
					date+=(cmonth-format.tm_mon+1)<<5;
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
							redraw(font, unavail, cmonth, w, md, format);
							hauldata(backlog, date, 1);
							hauldata(backlog, date, 0);
							info[backlog][2] = 0;
							backlog = backlog % 19 + 1;
							}
							if (cthread<19) {
							backlog = 0;
							info[cthread][1] = 1;
							unavail[cthread] = date;
							redraw(font, unavail, cmonth, w, md, format);
							hauldata(cthread, date, 0);
							pthread_create(&thread[cthread], NULL, subwin, &info[cthread]);
							}
						}
						if (i<19) {
						info[i][1] = 0;
						unavail[i] = 0;
						pthread_join(thread[i], NULL);
						hauldata(i, date, 1);
						redraw(font, unavail, cmonth, w, md, format);
						}
					}
				}
			}
			if (c.t==1) {
				if (c.txt==65361&&cmonth) {
				cmonth--;
				redraw(font, unavail, cmonth, w, md, format);
				}
				if (c.txt==65363&&cmonth!=format.tm_mon+11) {
				cmonth++;
				redraw(font, unavail, cmonth, w, md, format);
				}
				if (c.txt==105) {
				redraw(italic, unavail, cmonth, w, md, format);
				}
				if (c.txt==113) {
				dreg = format.tm_mon + (format.tm_year<<4);
				sign(dreg);
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
