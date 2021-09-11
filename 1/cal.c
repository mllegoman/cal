#include <exp.h>
#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// can do some things here:
 // make some good fonts
 // scale fonts
 // use x_init multiple times
  // multithreading
 // learn some unix time stuffs
 // DD/MM/YY segregation
  // optional ordering ^

void *subwin(void){
FILE *scache = fopen("/home/widower/.config/cal/.session", "a");
char base[];
unsigned long color;
pos = 0;
struct cache c;
init_x(0, "", "", 500, 500, 0, 0);
RegionFill(0, 0, 50, 50, RGB(0, 0, 0));
	while(1) { 
	Eve(&c);
		if (c.t==1) {
			if (c.txt==8) {

			} else {

			}
		}
		if (c.t==2) {
			if (1) {
			
			}
			if (1) {
			color = 0; // white
			}
			if (1) {
			break; // clear text
			}
		}
		if (c.t==3) {
		// get dimensions
		// RegionFill(0, 0, newd, newd, RGB(0, 0, 0));
		}
	}

fputs(tmp, scache);
fclose(scache);
}

int main() {
pthread_t thread_0;
time_t t = time(NULL);
struct tm time = *localtime(&t);
struct cache c;

init_x(0, "", "", 600, 600, 0, 0);
RegionFill(0, 0, 50, 50, RGB(0, 0, 0));
	while(1) { 
	Eve(&c);
		if (c.t==2) {
		break;
		}
	}
pthread_create(&thread_0, NULL, subwin, NULL);
pthread_join(thread_0, NULL);
close_x(0);
}
