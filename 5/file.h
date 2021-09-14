#include <stdio.h>
struct getdim {
unsigned int h;
unsigned int w;
};
extern struct getdim hw(char win);
extern void setdim(unsigned int h, unsigned int w, char win);
extern FILE *opensessionfile(char sesid);
extern void hauldata(char sesid, int date, char p);
extern void funnel(char sesid, char base[]);
extern char *getfont(char *fontn, char n);
