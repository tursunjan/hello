#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "sam2sv.h"

void sort_list( struct strce *strcell, unsigned long long int *InsPos1, unsigned long long int *InsPos2){

	sure_bp(strcell[0].pos, strcell[0].cigar, &bp[0], &ht[0]);
	sure_bp(strcell[1].pos, strcell[1].cigar, &bp[1], &ht[1]);
	
	if(bp[0]>bp[1]){
		bp_reg=bp[0];
		bp[0]=bp[1];
		bp[1]=bp_reg;
		ht_reg=ht[0];
		ht[0]=ht[1];
		ht[1]=ht_reg;
		chr_reg=strcell[0].chr;
		strcell[0].chr=strcell[1].chr;
		strcell[1].chr=chr_reg;
	}
	*InsPos1=((ht[0]&0x3)<<38)+bp[0]+((strcell[0].chr&0x003f)<<32);
	*InsPos2=((ht[1]&0x3)<<38)+bp[1]+((strcell[1].chr&0x003f)<<32);
	
}	
