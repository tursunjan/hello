#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

struct sam{
        char cigar[200];
        unsigned long int pos1;
	char chr[30];
};

void sure_bp(int pos, char *cigar, int *bp, int *ht);
void sure_bp_ins (int pos, char *cigar, int *bp, int *ht , int *en);
void read_sam_ins(FILE *fp);
void read_sam(FILE *fp);
