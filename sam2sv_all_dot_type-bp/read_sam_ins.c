#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "sam2sv.h"

void read_sam_ins(FILE *fp)
{
        struct sam *sam_inf=(struct sam*)malloc(10*sizeof(struct sam));
        int bp[2] , ht[2] ;
        int pbp, flag, pos1,  flag_reg=0;
        char cigar[200],chr[30];
        
	bp[0]=0;bp[1]=0;
        ht[1]=0;ht[0]=0;
        pbp=0;
        int ht_reg1[2];
        ht_reg1[0]=0;
        ht_reg1[1]=1;
        int en=0;
        while(!feof(fp))
        {
                fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
                while(strcmp(cigar,"*")==0)
                {
                        fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
                }
//                chr_num=chr2num(chr);   // change the chrom to num , in order to save conveniently
                if((flag&0xc0)!=(flag_reg&0xc0))
                {
                        if(pbp == 1)
                        {
                                en=0;
                                if(strcmp(sam_inf[0].cigar,"100M")!=0)
                                {
                                        sure_bp_ins (sam_inf[0].pos1, sam_inf[0].cigar, &bp[0], &ht[0], &en);
                                        if(en==1)
                                        {
						printf("%s\t%d\t%d\n",sam_inf[0].chr,bp[0],ht[0] );
                                        }
                                }

                        }

                        strcpy(sam_inf[0].cigar, cigar);
                        flag_reg=flag;
                        sam_inf[0].pos1=pos1;
			strcpy(sam_inf[0].chr, chr);
                        pbp=1;
                }
                else
                {
                        pbp++;
                }
        }
        free(sam_inf);
}

