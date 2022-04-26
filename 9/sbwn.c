#include <ssw.h>
#include "main.h"
#include "file.h"

// TODO
// need special delimiter for font type / italics vs reg / color font

void drawbuff(char *base) {
// drawstr(font, , , , );
}

void sbwnredraw() {

}

void *subwin(char *p) {
struct cache c;
struct getdim dim = hw(0);
char *font = getfont("default", 8);
char base[4096];
funnel(*p, base);
FILE *scache = opensessionfile(*p);
unsigned long txtclr;
unsigned int pos = 0;
base[0] = 0; // delete this

XI(0, "", "", dim.w, dim.h, 0, 0, *p);
Eve(&c, *p);
RegionFill(0, 0, dim.w, dim.h, RGB(0, 0, 0), *p);
while(*(p + 1)) {
	if (*(p + 2)) {
	fclose(scache);
	// allow time for copy
	scache = opensessionfile(*p);
	} 
	while(Pend(*p)) { 
	Eve(&c, *p);
		if (c.t==1) {
			if (c.txt==65288) {
			base[pos] = 0;
			pos-=!!pos;
			}
			if (c.txt<256) {
			base[pos++] = (char)c.txt;
			base[pos] = 0;
			}
			if (c.txt==65361) {
			pos--;
			}
			if (c.txt==65363) {
                        pos++;
                        }
		}
		if (c.t==2) {
			if (1) { // between 0,0 => w,h
			fputc((char)234, scache);
			fputs(base, scache);
			fputs(base, stdout);
			fputc((char)10, stdout);
			}
			if (1) { // between w,0 => 2w,h
			// insert link?
			}
			if (1) { /// between 2w,0 => 3w,h
			// clear all text (base)
			}
		}
		if (c.t==3) {
		RegionFill(0, 0, WW(*p), WH(*p), RGB(0, 0, 0), *p);
		}
	}
}
setdim(WH(*p), WW(*p), 0);
Clean(*p);
fclose(scache);
}
