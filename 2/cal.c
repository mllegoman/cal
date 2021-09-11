#include <ssw.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include "sbwn.h"

// can do some things here:
 // make some good fonts
 // scale fonts
 // learn some unix time stuffs
 // DD/MM/YY segregation
  // optional ordering ^

int main() {
struct cache c;
pthread_t thread[1];
char info[2];
time_t t = time(NULL);
struct tm time = *localtime(&t);

XI_();
XI(0, "", "", 600, 600, 0, 0);
Eve(&c);
RegionFill(0, 0, 600, 600, RGB(0, 0, 0));
info[0] = 1;
info[1] = 1;
	while(1) { 
	Eve(&c);
		if (c.t==2) {
		pthread_create(&thread[0], NULL, subwin, &info);
		break;
		}
	}

	while(1) {
	Eve(&c);
		if (c.t==2) {
		info[1] = 0;
		break;
		}
	}
pthread_join(thread[0], NULL);
XC(0);
}
