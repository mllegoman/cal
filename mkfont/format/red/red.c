#include "main.h"

uint32_t needn = 5;
uint32_t needed[] = {0b001101101011000010111100001110000,    //maxp
			0b01100011011011010110000101110000,  //cmap
			0b01100111011011000111100101100110,  //glyf
			0b01101100011011110110001101100001,  //loca
			0b01101000011001010110000101100100}; //head
char where (char s[4]) {
char i = 0;
	while (i < needn) {
		if ((s[0]<<24)+(s[1]<<16)+(s[2]<<8)+s[3]==needed[i]) {
		return i;
		}
	i++;
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
uint32_t offset[needn];
uint32_t length[needn];

i = 0;
while (i < ntable) {
associate[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F);
fgetc(F);fgetc(F);fgetc(F);fgetc(F);
toffset[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F);
tlength[i] = (fgetc(F)<<24) + (fgetc(F)<<16) + (fgetc(F)<<8) + fgetc(F);
i++;
}

j = 0;
while (j < needn) {
i = 0;
	while (1-(associate[i]==needed[j])) {
	i++;
	}
	offset[j] = toffset[i];
	length[j] = tlength[i];
j++;
}

fseek(F, offset[where("head")] + 336, 0);
uint16_t flavor = fgetc(F)+fgetc(F);
fseek(F, offset[where("maxp")] + 4, 0);
uint16_t nglyph = (fgetc(F)<<8) + fgetc(F);
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
	loca[i] = (fgetc(F)<<10) + (fgetc(F)<<2); // 16 bit in - 32 out
	i++;
	}
}

int16_t glyphs[5*(nglyph + 1)];
uint16_t t_len, pts; 

i = 0;
while (i < nglyph + 1) {
fseek(F, offset[where("glyf")] + loca[i], 0);
j = 0;
	while (j < 5) {
	glyphs[i*5+j] = ((fgetc(F)<<8) | fgetc(F));
	j++;
	}
fseek(F, ftell(F) + glyphs[i*5]*2, 0);
// glyphs[i*5] is location of points not point values
//pts = (fgetc(F)<<8) + fgetc(F);
t_len = (fgetc(F)<<8) + fgetc(F);
fseek(F, ftell(F) + t_len, 0);

i++;
}

fseek(F, offset[where("cmap")], 0);
fgetc(F);fgetc(F);
uint16_t cmaptn = (fgetc(F)<<8) + fgetc(F);
uint16_t PID[cmaptn];
uint16_t EID[cmaptn];
uint32_t s_table[cmaptn]
uint16_t format;

i = 0;
while (i < cmaptn) {
PID[i] = (fgetc(F)<<8) + fgetc(F);
EID[i] = (fgetc(F)<<8) + fgetc(F);
s_table = offset[where("cmap")] + (fgetc(F)<<24) + 
                                  (fgetc(F)<<16) + 
                                  (fgetc(F)<<8) + fgetc(F);
i++;
}

i = 0;
while (i < cmaptn) {
fseek(F, s_table[i], 0);
format = (fgetc(F)<<8) + fgetc(F);
	if (format > 6&&format < 14) { // get rid of "reserved" value
	fgetc(F);fgetc(F);
	}
t_len = (fgetc(F)<<8) + fgetc(F);
}


fclose(F);
fclose(O);
}
