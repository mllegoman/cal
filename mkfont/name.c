#include <stdio.h>
#include <unistd.h>

int main() {
char sesid = 11;
char charcount, suf;
char *user = getlogin();
char sesfile[63] = "/home/________________________________/.config/cal/.session__\0";

printf("%s\n", sesfile);

for (charcount = 6; user[charcount-6]; charcount++) {
sesfile[charcount] = user[charcount-6];
}

printf("%s\n", sesfile);

for (charcount = 37; sesfile[charcount]==95; charcount--) {
	for (suf = 0; suf < 23; suf++) {
	sesfile[charcount+suf] = sesfile[charcount+suf+1];
	}
sesfile[charcount+suf] = 0; // +1
}

printf("%s %d %d\n", sesfile, suf, charcount);

sesfile[charcount+suf-1] = 48 + sesid/10;
sesfile[charcount+suf] = 48 + sesid%10;

// FILE *F = fopen(sesfile, "a+");
printf("%s\n", sesfile);
}
