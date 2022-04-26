#include "main.h"
struct getdim {
uint32_t h;
uint32_t w;
};
extern struct getdim hw(char win);
extern void setdim(uint32_t h, uint32_t w, char win);
extern FILE *opensessionfile(char sesid);
extern void hauldata(char sesid, uint32_t date, char p);
extern void funnel(char sesid, char base[]);
extern char *getfont(char *fontn, char n);
void sign(unsigned int date);
char hasText(int date, char cmonth, char realmonth);
