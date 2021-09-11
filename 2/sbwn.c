#include <ssw.h>
#include <stdio.h>

void *subwin(char *p){
struct cache c;

char sesfile[37] = "/home/widower/.config/cal/.session___";
sesfile[34] = 48 + *p/100;
sesfile[35] = 48 + *p/10%10;
sesfile[36] = 48 + *p%10;
sesfile[37] = 0;

FILE *scache = fopen(sesfile, "a+");
char base[4096];
unsigned long txtclr;
unsigned int pos = 0;
base[0] = 0;
XI_();
XI(0, "", "", 500, 500, 0, 0);
Eve(&c);
RegionFill(0, 0, 500, 500, RGB(0, 0, 0));
while(*(p + 1)) {
	while(Pend()) { 
	Eve(&c);
		if (c.t==1) {
			if (c.txt[0]==8) {
			base[pos] = 0;
			pos-=!!pos;
			} else {
			base[pos++] = c.txt[0];
			base[pos] = 0;
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
		RegionFill(0, 0, 500, 500, RGB(0, 0, 0));
		}
	}
}
Clean();
fclose(scache);
}
