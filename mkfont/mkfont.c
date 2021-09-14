#include <ssw.h>
#include <stdio.h>

#define uchar unsigned char
#define uint unsigned int

// TODO:
// make things faster -- things are getting really slow
// resize window - prettymuch everything else
// make clearing individual curves easier
// unsigned int => unsigned char
// make writing 'unsigned [int|char]' easier

int adjpow(uint n) {
char i = 31;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

int approxdis(uchar x[20], uchar y[20], uchar n) {
char i;
uint tot = 0;
uint wh = WH(0);
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

void drawcurve(uchar x[20], uchar y[20], uchar n) {
uchar i, j;
uint slice[20];
uint wh = WH(0);
float t, tc, snbl, totx, toty;
tc = (float)1/adjpow((uint)approxdis(x, y, n))/2;
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
		RegionFill((uint)(totx*wh/256), (uint)(toty*wh/256), 1, 1, RGB(255, 255, 255), 0);
	}
}

void draw(uchar x[20][20], uchar y[20][20], uchar n[20], char l) {
RegionFill(0, 0, WW(0), WH(0), RGB(0, 0, 0), 0);

char i, j;
uint wh = WH(0);

if (l) {
RegionFill(0, wh/13, wh/2, 1, RGB(255, 128, 128), 0); 
RegionFill(0, 5*wh/13, wh/2, 1, RGB(255, 40, 40), 0); 
RegionFill(0, wh/2, wh/2, 1, RGB(255, 0, 0), 0); // halfway
RegionFill(0, 9*wh/13, wh/2, 1, RGB(255, 255, 255), 0); 

	for (i = 0; i < 20; i++) {
		for (j = 0; j < 20; j++) {
		RegionFill((uint)(x[i][j]*wh/256), (uint)(y[i][j]*wh/256), 1, 1, RGB(255, 255, 255), 0);
		}
	}
}

for (i = 0; i < 20; i++) {
	if (n[i]) {
	drawcurve(x[i], y[i], n[i]);
	}
}
}

int main() {
FILE *F = fopen("default", "a+");
struct cache c;
uchar x[20][20];
uchar y[20][20];
uchar n[20];
uchar m, xn, i, j, cu, tmpx, tmpy;
int tot;
char alpha;
char l = 1;

for (i = 0; i < 20; i++) {
n[i] = 0;
	for (j = 0; j < 20; j++) {
	x[i][j] = 0;
	y[i][j] = 0;
	}
}

XI(0, "", "", 256, 512, 0, 0, 0);
Eve(&c, 0);
draw(x, y, n, l);
	while(1) {
	c.t = 3;
	printf("requesting alpha:\n");
		while(c.t!=1) {
		Eve(&c, 0);
		}
	alpha = c.txt[0];
	printf("got our alpha: %c\n", alpha);
	c.txt[0] = 0;
	m = 0;
		while(c.txt[0]!=115){
			while(Pend(0)){
			if (Pend(0) > 50) {
				while(1) {
				Eve(&c, 0);
					if (Pend(0) < 10) {
					break;
					}
				}
			}
			Eve(&c, 0);
				if (c.t==3) {
				draw(x, y, n, l);
				}
			
				if (c.t==2) {
					for (i = 0; i < 20; i++) {
						for (j = 0; j < 20; j++) {
						tot = 0;
						tot+=dis((char)(c.x*256/WH(0)), x[i][j]);
						tot+=dis((char)(c.y*256/WH(0)), y[i][j]);
							if (tot < 10) {
							c.t = 3;
							tmpx = x[i][j];
							tmpy = y[i][j]; 
								while(c.t!=2) {
								Eve(&c, 0);
								}
								// if c.t==1&&c.txt[0]=="c" { clear curve }
								for (i = 0; i < 20; i++) {
									for (j = 0; j < 20; j++) {
									tot = 0;
									tot+=dis(x[i][j], tmpx);
									tot+=dis(y[i][j], tmpy);
										if (tot < 10) {
										x[i][j] = (uchar)(c.x*256/WH(0));
										y[i][j] = (uchar)(c.y*256/WH(0));
										}
									}
								}
							draw(x, y, n, l);
							}
						}
					}
				}
			
				if (c.t==1) {
					if (c.txt[0]==113) {
					fclose(F);
					Clean(0);
					XX(0);
					}
					if (c.txt[0]==112) {
						for (i = 0; i < 20; i++) {
							for (j = 0; j < 20; j++) {
								if (x[i][j]==0) {
								break;
								}
							printf("[%d,%d]", x[i][j], y[i][j]);
							}
						printf("n=%d\n", n[i]);
						}
					printf("\n");
					}
					if (c.txt[0]==110&&m < 20) {
					c.t = 3;
						printf("requesting n:\n");
						while(c.t!=1) {
						Eve(&c, 0);
							if (c.txt[0] > 49&&c.txt[0] < 58) {
							xn = c.txt[0] - 48;
							printf("got our n: %d\n", xn);
							n[m] = xn;
								while (c.txt[0]!=13) {
								Eve(&c, 0);
									if (c.txt[0] > 48&&c.txt[0] < 49 + xn) {
									cu = c.txt[0] - 49;
									printf("%d\n", cu);
										while(c.t!=2) {
										Eve(&c, 0);
											if (c.t==2) {
												for (i = 0; i < 20; i++) {
													for (j = 0; j < 20; j++) {
													tot = 0;
													tot+=dis((char)(c.x*256/WH(0)), x[i][j]);
													tot+=dis((char)(c.y*256/WH(0)), y[i][j]);
														if (tot < 10&&m!=i&&cu!=j) {
														x[m][cu] = x[i][j];
														y[m][cu] = y[i][j];
														draw(x, y, n, l);
														}
													}
												}
												if (x[m][cu]==0) {
												x[m][cu] = c.x*256/WH(0);
												y[m][cu] = c.y*256/WH(0);
												draw(x, y, n, l);
												}
											}
										}
									} // holy jesus, brackets
								}
							} else {
							c.t = 3;
							}
						}
					m++;
					draw(x, y, n, l);
					}
					if (c.txt[0]==108) {
					l = 1 - l;
					draw(x, y, n, l);
					}
					if (c.txt[0]==99) {
					m = 0;
						for (i = 0; i < 20; i++) {
						n[i] = 0;
							for (j = 0; j < 20; j++) {
							x[i][j] = 0;
							y[i][j] = 0;
							}
						}
					draw(x, y, n, l);
					}
				}
			}
		}

	fputc(alpha, F);
	fputc((char)58, F);
	fputc((char)2, F);
		for (i = 0; i < m; i++) {
			for (j = 0; j < n[i]; j++) {
			fputc(x[i][j], F);
			fputc(y[i][j], F);
				if (j < n[i] - 1) {
				fputc((char)0, F);
				}
			}
		fputc((char)1, F);
		}
		for (i = 0; i < 20; i++) {
		n[i] = 0;
			for (j = 0; j < 20; j++) {
			x[i][j] = 0;
			y[i][j] = 0;
			}
		}
	draw(x, y, n, l);
	}
}
