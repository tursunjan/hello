#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "sam2sv.h"	
void read_sam(FILE *fp){
	struct sam *sam_inf=(struct sam*)malloc(20000*sizeof(struct sam));
	int bp[2] , ht[2] ;
	int bp_reg,ht_reg;
	int i ,pbp, flag, pos1, flag_reg=0;
	char cigar[200],chr[30],chr_temp[30];
	
	bp[0]=0;bp[1]=0;
	ht[1]=0;ht[0]=0;
	pbp=0;
	while(!feof(fp)){
		fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
		while(strcmp(cigar,"*")==0)
		{	
			fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
		}
//		chr_num=chr2num(chr);	// change the chrom to num , in order to save conveniently	
		if((flag&0xc0)!=(flag_reg&0xc0))
		{
			if(pbp >= 2)
			{
				if(pbp%2==0 )
				//&& ((sam_inf[0].flag&0x2)!=0 || (sam_inf[1].flag&0x2)!=0) )
				{
					for( i=0;i<pbp;i+=2 )
					{
						sure_bp(sam_inf[i+0].pos1, sam_inf[i+0].cigar, &bp[0], &ht[0]);
						sure_bp(sam_inf[i+1].pos1, sam_inf[i+1].cigar, &bp[1], &ht[1]);
						if(bp[0]>bp[1]){
							bp_reg=bp[0];
							bp[0]=bp[1];
							bp[1]=bp_reg;
							ht_reg=ht[0];
							ht[0]=ht[1];
							ht[1]=ht_reg;
							strcpy(chr_temp , sam_inf[i+0].chr);
							strcpy(sam_inf[i+0].chr , sam_inf[i+1].chr);
							strcpy(sam_inf[i+1].chr , chr_temp);
						//	chr_reg=sam_inf[0].chr;
						//	sam_inf[i+0].chr=sam_inf[i+1].chr;
						//	sam_inf[i+1].chr=chr_reg;
						}
						printf("%s\t%d\t%d\t%s\t%d\t%d\n",sam_inf[i+0].chr,bp[0],ht[0],sam_inf[i+1].chr,bp[1],ht[1] );
					//	bp[0]=0;bp[1]=0; ht[1]=0;ht[0]=0;
					}
				} 
				else
				{
					for( i=1;i<pbp;i+=2 )
                                        {
                                                sure_bp(sam_inf[i+0].pos1, sam_inf[i+0].cigar, &bp[0], &ht[0]);
                                                sure_bp(sam_inf[i+1].pos1, sam_inf[i+1].cigar, &bp[1], &ht[1]);
                                                if(bp[0]>bp[1]){
                                                        bp_reg=bp[0];
                                                        bp[0]=bp[1];
                                                        bp[1]=bp_reg;
                                                        ht_reg=ht[0];
                                                        ht[0]=ht[1];
                                                        ht[1]=ht_reg;
							strcpy(chr_temp , sam_inf[0].chr);
                                                        strcpy(sam_inf[i+0].chr , sam_inf[i+1].chr);
                                                        strcpy(sam_inf[i+1].chr , chr_temp);
                                              //        chr_reg=sam_inf[i+0].chr;
                                              //          sam_inf[i+0].chr=sam_inf[i+1].chr;
                                              //          sam_inf[i+1].chr=chr_reg;
                                                }
						printf("%s\t%d\t%d\t%s\t%d\t%d\n",sam_inf[i+0].chr,bp[0],ht[0],sam_inf[i+1].chr,bp[1],ht[1] );
					//	bp[0]=0;bp[1]=0; ht[1]=0;ht[0]=0;
                                        }

				} 
			}
	/*		for(i=0;i<=abp;i++)
			{
				sam_inf[i].flag=0;
				memset(sam_inf[i].cigar,200,0);
				sam_inf[i].pos1=0;
				memset(sam_inf[i].chr,30,0);
			}*/
			pbp=0;
			strcpy(sam_inf[0].cigar, cigar);
			flag_reg=flag;
                        sam_inf[0].pos1=pos1;
			strcpy(sam_inf[0].chr, chr);
                        pbp++;			
		}
		else
		{
			if(pbp < 10000)
			{
				strcpy(sam_inf[pbp].cigar, cigar);
				sam_inf[pbp].pos1=pos1;
				strcpy(sam_inf[pbp].chr, chr);
				pbp++;
			}
			else 
				pbp=pbp;
		}
	}
	free(sam_inf);
}
