#include "main.h"

uint32_t needn = 5;
uint32_t needed[needn]; 
needed[0] = ('m'<<32) + ('a'<<16) + ('x'<<8) + 'p'; // may seem strange now
needed[1] = ('c'<<32) + ('m'<<16) + ('a'<<8) + 'p'; // but better font support depends on this
needed[2] = ('g'<<32) + ('l'<<16) + ('y'<<8) + 'p';
needed[3] = ('l'<<32) + ('o'<<16) + ('c'<<8) + 'a';
needed[4] = ('h'<<32) + ('e'<<16) + ('a'<<8) + 'd';

char where (char s[4]) {
char i = 0;
	while (i < needn) {
		if ((s[0]<<24)+(s[0]<<16)+(s[0]<<8)+s[3]==needed[i]) {
		return i;
		}
	}
return needn;
}

int main (s_uint argc, char **argv) {
if (argc < 2) {
return 1;
}
FILE *F = fopen(argv[1], "r");
FILE *O = fopen(argv[2], "w");
if (F==0||O==0) {
return 1;
}

uint32_t ntable, i, j;
fseek(F, 4, 0);
ntable = (fgetc(F)<<8) + fgetc(F);
fseek(F, 12, 0);
uint32_t associate[ntable];
uint32_t toffset[ntable];
uint32_t tlength[ntable];
uint32_t offset[4];
uint32_t length[4];

i = 0
while (i < ntable) {
associate[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F);
fgetc(F);fgetc(F);fgetc(F);fgetc(F);
toffset[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F);
fgetc(F);fgetc(F);fgetc(F);fgetc(F);
tlength[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F);
i++;
}

j = 0;
while (j < 4) {
	i = 0;
	while (1-(associate[i]==needed[j])) {
	i++;
	}
	offset[j] = toffset[i];
	length[j] = tlength[i];
j++;
}

fseek(F, offset[where("head")] + 336, 0);
uint32_t flavor = fgetc(F)+fgetc(F)+fgetc(F)+fgetc(F);
printf("%d\n", flavor);
fseek(F, offset[where("maxp")] + 4, 0);
uint16_t nglyph = (fgetc(F)<<8) + fgetc(F);
printf("%d\n", nglyph);
fseek(F, offset[where("loca")], 0);
uint32_t loca[nglyph+1];

i = 0;
if (flavor) {
	while (i < nglyph + 1) {
	loca[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F); // 32 bit
	i++;
	}
} else {
	while (i < nglyph + 1) {
	loca[i] = ((fgetc(F)<<10) + (fgetc(F)<<2); // 16 bit in - 32 out
	i++;
	}
}

uint16 glyphs[5*(nglyph + 1)];

i = 0;
while (i < nglyphs + 1) {
fseek(F, loca[i], 0);
	j = 0;
	while (j < 5) {
	glyphs[i*5+j] = ((fgetc(F)<<8) | fgetc(F));
	j++;
	}
i++;
}

// read glyph table?

fseek(F, offset[where("cmap")], 0);

// figure out cmap

fclose(F);
fclose(O);
}
