 #include <stdio.h>
#include <stdlib.h>
#include "cells.h"
#include "../synth/synth.c"
#include <string.h>

void transpose32(unsigned vecfrom[32], unsigned vecto[32]) {
  unsigned bit, word;
  for (word = 0; word < 32; word++)
    vecto[word] = 0;
  for (bit = 0; bit < 32; bit++)
    for (word = 0; word < 32; word++)
      vecto[bit] = vecto[bit] | (( (vecfrom[word] & (1 << bit)) >> bit) << word);
}

#define MDTYPE_ONE  0xFFFFFFFF
#define MDTYPE_ZERO 0x0

unsigned tick = 0;
// #define TICK(A) printf("=============================================================================================\n\n\n<%d> %s\n\n\n=============================================================================================\n", tick++, #A)
#define TICK(A)

void main() {
	MDTYPE clk = 0;
	MDTYPE rst = 0;
	MDTYPE ld = 0;
	MDTYPE done = 0;
	MDTYPE x[32], t_x[32];
	MDTYPE e[32], t_e[32];
	MDTYPE y[32], t_y[32];

	memset(x,      0, 32*sizeof(MDTYPE));
	memset(e,      0, 32*sizeof(MDTYPE));
	memset(y,      0, 32*sizeof(MDTYPE));
	x[0] = 0xABCDEF;
	e[0] = 0x654321;
	transpose32(x, t_x);
	transpose32(e, t_e);

	rst = MDTYPE_ZERO;
	TICK(rst);
	pow32(clk, rst, ld, &done, t_x, t_e, t_y);
	rst = MDTYPE_ONE;

	// ld x, e
	ld = MDTYPE_ONE;
	TICK(ld);
	pow32(clk, rst, ld, &done, t_x, t_e, t_y);
	ld = MDTYPE_ZERO;

	// compute result	
	unsigned limit = 0;
	do {
		TICK(crunch);
		pow32(clk, rst, ld, &done, t_x, t_e, t_y);
		limit++;
    } while ((done != MDTYPE_ONE) && (limit < 500));

    printf("Iterations: %d\n", limit);
	transpose32(t_y, y);

	printf("x %x\n", x[0]);
	printf("e %x\n", e[0]);
	printf("y %x\n", y[0]);

}