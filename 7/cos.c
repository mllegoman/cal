#include <stdio.h>

float cosine(float x) {
return 1 - x*x/2 + x*x*x*x/24 - x*x*x*x*x*x/720 + x*x*x*x*x*x*x*x/40320;

//  - x*x*x*x*x*x*x*x*x*x/3614400;

}

float sine(float x) {
return x - x*x*x/6 + x*x*x*x*x/120 - x*x*x*x*x*x*x/5040;
}

int main () {
printf("%f\n", sine(0));
}
