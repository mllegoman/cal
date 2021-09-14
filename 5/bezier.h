extern void *rotate(void *ptr, void *ptr1, float angle, char type); // char/int return
extern unsigned char *italicize(unsigned char *font); // use malloc
extern void drawcurve(unsigned long rgb, unsigned int *x, unsigned int *y, unsigned char n, char win);
extern void drawstr(unsigned char *font, unsigned char str[10], unsigned int x, unsigned int y, unsigned char dscl, char win);
