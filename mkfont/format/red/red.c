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

int16_t *getpts(uint16_t n, FILE *F) {
int16_t *pts = malloc(n*2*3);
// remember flag logic
uint8_t repeat;
uint8_t flags;
uint8_t sizes[n*2];
uint8_t xtreat[n], ytreat[n];
uint32_t i = 0;
	while (i < n) {
	flags = fgetc(F);
	pts[i*3] = flags&1;
	sizes[i*2  ] = (flags>>1)&1;
	sizes[i*2+1] = (flags>>2)&1;
	xtreat[i] = (flags&2) + ((flags>>4)&1);
	ytreat[i] = ((flags>>1)&2) + ((flags>>5)&1);
		if ((flags>>3)&1) {
		repeat = fgetc(F);
			while (repeat) {
			repeat--;
			i++;
			pts[i*3] = flags&1;
			sizes[i*2  ] = (flags>>1)&1;
			sizes[i*2+1] = (flags>>2)&1;
			xtreat[i] = (flags&2) + ((flags>>4)&1); 
			ytreat[i] = ((flags>>1)&2) + ((flags>>5)&1);
			}
		}
	i++;
	}
i = 0;
pts[1] = 0;
pts[2] = 0;
	while (i < n) {	// 0 for signed 16, 1 for copy, 2 for positive 8 bit value, 3 for begative 8 bit
		if (xtreat[i]==3) {
		pts[i*3+1] = pts[(i-!!i)*3+1] + fgetc(F);
		}
		if (xtreat[i]==2) {
		pts[i*3+1] = pts[(i-!!i)*3+1] - fgetc(F);
		}
		if (xtreat[i]==1) {
		pts[i*3+1] = pts[(i-!!i)*3+1];
		}
		if (xtreat[i]==0) {
		pts[i*3+1] = pts[(i-!!i)*3+1] + (fgetc(F)<<8) + fgetc(F);
		}
	i++;
	}
i = 0;
	while (i < n) {	// 0 for signed 16, 1 for copy, 2 for positive 8 bit value, 3 for begative 8 bit
		if (ytreat[i]==3) {
		pts[i*3+2] = pts[(i-!!i)*3+2] + fgetc(F);
		}
		if (ytreat[i]==2) {
		pts[i*3+2] = pts[(i-!!i)*3+2] - fgetc(F);
		}
		if (ytreat[i]==1) {
		pts[i*3+2] = pts[(i-!!i)*3+2];
		}
		if (ytreat[i]==0) {
		pts[i*3+2] = pts[(i-!!i)*3+2] + (fgetc(F)<<8) + fgetc(F);
		}
	i++;
	}

return pts;
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
fseek(F, ftell(F) + 24, 0);
// (fgetc(F)<<8) + fgetc(F));
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

int16_t glyphs[nglyph + 1][5];
uint16_t t_len, pts; 
uint16_t *ctr[nglyph + 1];
int16_t *points[nglyph + 1];

i = 0;
while (i < nglyph) {
fseek(F, offset[where("glyf")] + loca[i], 0);
j = 0;
	while (j < 5) {
	glyphs[i][j] = ((fgetc(F)<<8) | fgetc(F));
	j++;
	}
j = 0;
ctr[i] = malloc(2*glyphs[i][0]);
	while (j < glyphs[i][0]) {
	ctr[i][j] = (fgetc(F)<<8) + fgetc(F);
	printf("%d\n", ctr[i][j]);
	j++;
	}
t_len = (fgetc(F)<<8) + fgetc(F);
fseek(F, ftell(F) + t_len, 0); // skip instructions
t_len = j - 1;
//printf("%d %d %d\n", t_len&1, (t_len>>7)&1, (t_len>>6)&1,(t_len>>5)&1,(t_len>>4)&1,(t_len>>3)&1,(t_len>>2)&1);
points[i] = getpts(ctr[i][t_len] + 1, F);
j = 0; // start only instance of testing
	while (j < ctr[i][t_len] + 1) {
	printf("r: %d x: %d y: %d\n", points[i][j*3], points[i][j*3+1], points[i][j*3+2]);
	j++;
	}
i++;
}

fseek(F, offset[where("cmap")], 0);
fgetc(F);fgetc(F);
uint16_t cmaptn = (fgetc(F)<<8) + fgetc(F);
uint16_t PID[cmaptn];
uint16_t EID[cmaptn];
uint32_t s_table[cmaptn];
uint16_t format;

i = 0;
while (i < cmaptn) {
PID[i] = (fgetc(F)<<8) + fgetc(F);
EID[i] = (fgetc(F)<<8) + fgetc(F);
s_table[i] = offset[where("cmap")] + (fgetc(F)<<24) + 
                                     (fgetc(F)<<16) + 
                                     (fgetc(F)<<8) + fgetc(F);
i++;
}
return 0;
i = 0;
while (i < cmaptn) {
fseek(F, offset[where("cmap")] + s_table[i], 0);
format = (fgetc(F)<<8) + fgetc(F);
	if (format > 6&&format < 14) { // get rid of "reserved" value
	fgetc(F);fgetc(F);
	}
t_len = (fgetc(F)<<8) + fgetc(F);
}


fclose(F);
fclose(O);
}
