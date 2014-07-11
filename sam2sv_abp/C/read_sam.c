#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "sam2sv.h"
	
void read_sam(FILE *fp, struct PosNode **L, struct PosNode **tail){

	struct sam *sam_inf=(struct sam*)malloc(1000000*sizeof(struct sam));
	unsigned long long int bp[2] , ht[2] ;
	unsigned long long int InsPos1,InsPos2,bp_reg,ht_reg,chr_reg;
	int i,pbp, flag, pos1, chr_num , flag_reg=0;
	char cigar[100],chr[20];
	bp[0]=0;bp[1]=0;
	ht[0]=0;ht[1]=0;
	pbp=0;
	unsigned long long int ht_reg1[2];
	ht_reg1[0]=0;
	ht_reg1[1]=1;
	while(!feof(fp)){
			fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
		while(strcmp(cigar,"*")==0)
		{	
			fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
		}
		chr_num=chr2num(chr);	// change the chrom to num , in order to save conveniently	
		if((flag&0xc0)!=(flag_reg&0xc0))
		{
			if(pbp >= 2)
			{
			//	if(pbp%2==0 && ((sam_inf[0].flag&0x2)!=0 || (sam_inf[1].flag&0x2)!=0) )
				{
					for( i=0;i<2;i+=2 )
					{
						sure_bp(sam_inf[i+0].pos1,sam_inf[i+0].flag, sam_inf[i+0].cigar, &bp[0], &ht[0]);
						sure_bp(sam_inf[i+1].pos1,sam_inf[i+0].flag, sam_inf[i+1].cigar, &bp[1], &ht[1]);
						if(bp[0]>bp[1]){
							bp_reg=bp[0];
							bp[0]=bp[1];
							bp[1]=bp_reg;
							ht_reg=ht[0];
							ht[0]=ht[1];
							ht[1]=ht_reg;
							chr_reg=sam_inf[i+0].chr;
							sam_inf[i+0].chr=sam_inf[i+1].chr;
							sam_inf[i+1].chr=chr_reg;
						}
						if(ht[0])
						{
							InsPos1=((ht_reg1[0]&0x3)<<38)+bp[0]+((sam_inf[i+0].chr&0x003f)<<32);//h
							InsPos2=((ht_reg1[1]&0x3)<<38)+bp[0]+((sam_inf[i+0].chr&0x003f)<<32)+0x10000000000;//t
						}
						else
						{
							InsPos1=((ht_reg1[0]&0x3)<<38)+bp[0]+((sam_inf[i+0].chr&0x003f)<<32)+0x10000000000;
							InsPos2=((ht_reg1[1]&0x3)<<38)+bp[0]+((sam_inf[i+0].chr&0x003f)<<32);
						}
						BuildList( &(*L), &(*tail), InsPos1, InsPos2 );
						InsPos1=0;InsPos2=0;
						if(ht[1])
                                                {
                                                        InsPos1=((ht_reg1[0]&0x3)<<38)+bp[1]+((sam_inf[i+1].chr&0x003f)<<32);//h
                                                        InsPos2=((ht_reg1[1]&0x3)<<38)+bp[1]+((sam_inf[i+1].chr&0x003f)<<32)+0x10000000000;//t
                                                }
                                                else
                                                {
                                                        InsPos1=((ht_reg1[0]&0x3)<<38)+bp[1]+((sam_inf[i+1].chr&0x003f)<<32)+0x10000000000;
                                                        InsPos2=((ht_reg1[1]&0x3)<<38)+bp[1]+((sam_inf[i+1].chr&0x003f)<<32);
                                                }
						BuildList( &(*L), &(*tail), InsPos1, InsPos2 );
					}
				}  
		/*		else
				{
					for( i=1;i<pbp;i+=2 )
                                        {
						sure_bp(sam_inf[i+0].pos1,sam_inf[i+0].flag, sam_inf[i+0].cigar, &bp[0], &ht[0]);
						sure_bp(sam_inf[i+1].pos1,sam_inf[i+0].flag, sam_inf[i+1].cigar, &bp[1], &ht[1]);
						if(bp[0]>bp[1]){
						        bp_reg=bp[0];
						        bp[0]=bp[1];
						        bp[1]=bp_reg;
						        ht_reg=ht[0];
						        ht[0]=ht[1];
						        ht[1]=ht_reg;
						        chr_reg=sam_inf[i+0].chr;
						        sam_inf[i+0].chr=sam_inf[i+1].chr;
						        sam_inf[i+1].chr=chr_reg;
						}
						InsPos1=((ht[0]&0x3)<<38)+bp[0]+((sam_inf[i+0].chr&0x003f)<<32);
						InsPos2=((ht[1]&0x3)<<38)+bp[1]+((sam_inf[i+1].chr&0x003f)<<32);
                                                BuildList( &(*L), &(*tail), InsPos1, InsPos2 );
                                        }
				}*/
			}
			for(i=0;i<=pbp;i++)
			{
				sam_inf[pbp].flag=0;
				memset(sam_inf[pbp].cigar,20,0);
				sam_inf[pbp].pos1=0;
				sam_inf[1].chr=0;
			}
			pbp=0;
			strcpy(sam_inf[pbp].cigar, cigar);
			flag_reg=flag;
                        sam_inf[pbp].pos1=pos1;
			sam_inf[pbp].flag=flag;
                        sam_inf[pbp].chr=chr_num;
                        pbp++;			
		}
		else
		{
			strcpy(sam_inf[pbp].cigar, cigar);
			sam_inf[pbp].pos1=pos1;
			sam_inf[pbp].chr=chr_num;
			sam_inf[pbp].flag=flag;
			pbp++;
		}
	}
	free(sam_inf);
}
