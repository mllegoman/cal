#include <ssw.h>
#include <stdio.h>

// TODO:
// make things faster
// 

int adjpow(int n) {
int i = 31;
	while ((n&((~0)<<i))==0) {
	i--;
	}
i--;
return ((n>>i)+((n>>i)&1))<<i;
}

int approxdis(int x[20], int y[20], int n) {
int tot = 0;
int i;
	for (i = 0; i + 1 < n; i++) {
	tot+=(((x[i]*WW(0)/500)|(x[i+1]*WW(0)/500))<<1)-(x[i]*WW(0)/500)-(x[i+1]*WW(0)/500);
	tot+=(((y[i]*WW(0)/500)|(y[i+1]*WW(0)/500))<<1)-(y[i]*WW(0)/500)-(y[i+1]*WW(0)/500);
	}
return tot;
}

int dis(int m, int n) {
	if (m - n < n - m) {
	return n - m;
	}
return m - n;
}

void draw(unsigned int x[20], unsigned int y[20], int n, char l) {
int m, i, j;
int slice[20];
m = 0;
i = 0;
j = 0;
float t, tc, snbl, totx, toty;
t = 0;
tc = (float)1/adjpow(approxdis(x, y, n)*500/WW(0))/2;
snbl = 1;
totx = 0;
toty = 0;
	if (l) {
		for (m = 0; m < n; m++) {
		RegionFill(x[m]*WW(0)/500, y[m]*WW(0)/500, 1, 1, RGB(255, 255, 255), 0);
		}
	}

slice[0] = 1;

	for (i = 1; i < (n + 1)/2; i++) {
	slice[i] = slice[i - 1] * (n - i)/i;
	}

	for (i = n - 1; i > (n - 1)/2; i--) {
	slice[i] = slice[n - i - 1];
	}

	for (t = 0; (int)t==0; t+=tc+tc*(t>0.25||t>0.75)) {
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
		RegionFill((int)totx*WW(0)/500, (int)toty*WW(0)/500, 1, 1, RGB(255, 255, 255), 0);
	}
}

void redraw(unsigned int x[20][20], unsigned int y[20][20], int n[20], char l) {
RegionFill(0, 0, WW(0), WH(0), RGB(0, 0, 0), 0);


if (l) {
RegionFill(75*WW(0)/500, 50*WW(0)/500,  350*WW(0)/500, 1, RGB(255, 255, 255), 0);
RegionFill(75*WW(0)/500, 167*WW(0)/500, 350*WW(0)/500, 1, RGB(255, 255, 255), 0);
RegionFill(75*WW(0)/500, 250*WW(0)/500, 350*WW(0)/500, 1, RGB(255, 255, 255), 0); // halfway
RegionFill(75*WW(0)/500, 450*WW(0)/500, 350*WW(0)/500, 1, RGB(255, 255, 255), 0);
}

int m;
	for (m = 0; m < 19; m++) {
		if (n[m]) {
		draw(x[m], y[m], n[m], l);
		}
	}
}

int main() {
FILE *F = fopen("default", "a+");
struct cache c;
unsigned int x[20][20];
unsigned int y[20][20];
char *one;
int xn[20];
int m, n, i, j, tot, cu, tmpx, tmpy;
char alpha;
char l = 1;
m = 0;
n = 0;
tot = 0;
cu = 0;
for (i = 0; i < 19; i++) {
xn[i] = 0;
	for (j = 0; j < 19; j++) {
	x[i][j] = 0;
	y[i][j] = 0;
	}
}

XI(0, "", "", 500, 500, 0, 0, 0);
Eve(&c, 0);
redraw(x, y, xn, l);
	while(1) {
	c.t = 3;
		while(c.t!=1) {
		Eve(&c, 0);
		}
	alpha = c.txt[0];
	printf("got our alpha: %d\n", alpha);
		
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
				redraw(x, y, xn, l);
				}
			
				if (c.t==2) {
					for (i = 0; i < 19; i++) {
						for (j = 0; j < 19; j++) {
						tot = 0;
						tot+=dis(c.x*500/WW(0), x[i][j]);
						tot+=dis(c.y*500/WW(0), y[i][j]);
							if (tot < 10) {
							c.t = 3;
							tmpx = x[i][j];
							tmpy = y[i][j]; 
								while(c.t!=2) {
								Eve(&c, 0);
								}
								for (i = 0; i < 19; i++) {
									for (j = 0; j < 19; j++) {
									tot = 0;
									tot+=dis(x[i][j], tmpx);
									tot+=dis(y[i][j], tmpy);
										if (tot < 10) {
										x[i][j] = c.x*500/WW(0);
										y[i][j] = c.y*500/WW(0);
										}
									}
								}
							redraw(x, y, xn, l);
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
						for (i = 0; i < 19; i++) {
							for (j = 0; j < 19; j++) {
								if (x[i][j]==0) {
								break;
								}
							printf("[%d,%d]", x[i][j], y[i][j]);
							}
						printf("n=%d\n", xn[i]);
						}
					printf("\n");
					}
					if (c.txt[0]==110&&m < 20) {
					c.t = 3;
						while(c.t!=1) {
						Eve(&c, 0);
							if (c.txt[0] > 49&&c.txt[0] < 58) {
							n = c.txt[0] - 48;
							printf("got our n: %d\n", n);
							xn[m] = n;
								while (c.txt[0]!=13) {
								Eve(&c, 0);
									if (c.txt[0] > 48&&c.txt[0] < 49 + n) {
									cu = c.txt[0] - 49;
									printf("%d\n", cu);
										while(c.t!=2) {
										Eve(&c, 0);
											if (c.t==2) {
												for (i = 0; i < 19; i++) {
													for (j = 0; j < 19; j++) {
													tot = 0;
													tot+=dis(c.x*500/WW(0), x[i][j]);
													tot+=dis(c.y*500/WW(0), y[i][j]);
														if (tot < 10&&m!=i&&cu!=j) {
														x[m][cu] = x[i][j];
														y[m][cu] = y[i][j];
														redraw(x, y, xn, l);
														}
													}
												}
												if (x[m][cu]==0) {
												x[m][cu] = c.x*500/WW(0);
												y[m][cu] = c.y*500/WW(0);
												redraw(x, y, xn, l);
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
					redraw(x, y, xn, l);
					}
					if (c.txt[0]==108) {
					l = 1 - l;
					redraw(x, y, xn, l);
					}
					if (c.txt[0]==99) {
					m = 0;
						for (i = 0; i < 19; i++) {
						xn[i] = 0;
							for (j = 0; j < 19; j++) {
							x[i][j] = 0;
							y[i][j] = 0;
							}
						}
					redraw(x, y, xn, l);
					}
				}
			}
		}
	fputc(alpha, F);
	fputc((char)58, F);
		for (i = 0; i < m; i++) {
			for (j = 0; j < xn[i]; j++) {
			x[i][j]/=2;
			one = (char *)&x[i][j];
			fputc(one[0], F);
			y[i][j]/=2;
			one = (char *)&y[i][j];
			fputc(one[0], F);
				if (j==xn[i]-1) {
				fputc((char)16, F);
				} else {
				fputc((char)0, F);
				}
			}
		}
	m = 0;
		for (i = 0; i < 19; i++) {
		xn[i] = 0;
			for (j = 0; j < 19; j++) {
			x[i][j] = 0;
			y[i][j] = 0;
			}
		}
	redraw(x, y, xn, l);
	}
}
