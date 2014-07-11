#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "sam2sv.h"
	
void read_sam_ins(FILE *fp, struct PosNode **L, struct PosNode **tail)
{
	struct sam *sam_inf=(struct sam*)malloc(1000000*sizeof(struct sam));
	unsigned long long int bp[2] , ht[2] ;
	unsigned long long int InsPos1;
	unsigned long long int InsPos2;
	int i,pbp, flag, pos1, chr_num , flag_reg=0;
	char cigar[20],chr[20];
	bp[0]=0;bp[1]=0;
	ht[1]=0;ht[0]=0;
	pbp=0;
	unsigned long long int ht_reg1[2];
	ht_reg1[0]=0;
	ht_reg1[1]=1;
	while(!feof(fp))
	{
		fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
		while(strcmp(cigar,"*")==0)
		{	
			fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
		}
		chr_num=chr2num(chr);	// change the chrom to num , in order to save conveniently	
		if((flag&0xc0)!=(flag_reg&0xc0))
		{
			if(pbp == 1)
			{
				
				if(strcmp(sam_inf[0].cigar,"100M")!=0)
				{	
					sure_bp (sam_inf[0].pos1,sam_inf[0].flag, sam_inf[0].cigar, &bp[0], &ht[0]);
					if(ht[0])
					{
						InsPos1 = ((ht_reg1[0]&0x3)<<38)+bp[0]+((sam_inf[0].chr&0x003f)<<32);
						InsPos2 = ((ht_reg1[1]&0x3)<<38)+bp[0]+((sam_inf[0].chr&0x003f)<<32)+0x10000000000;
					}
					else
					{
						InsPos1 = ((ht_reg1[0]&0x3)<<38)+bp[0]+((sam_inf[0].chr&0x003f)<<32)+0x10000000000;
                                                InsPos2 = ((ht_reg1[1]&0x3)<<38)+bp[0]+((sam_inf[0].chr&0x003f)<<32);
					}
					BuildList( &(*L), &(*tail), InsPos1,InsPos2 );
				}
				
			/*	if(strcmp(sam_inf[1].cigar,"100M")!=0 )
				{	
					sure_bp (sam_inf[1].pos1,sam_inf[1].flag, sam_inf[1].cigar, &bp[0], &ht[0]);
					InsPos1 = ((ht[0]&0x3)<<38)+bp[0]+((sam_inf[1].chr&0x003f)<<32);
					BuildList_ins( &(*L), &(*tail), InsPos1 );					
				}*/
			}
			for(i=0;i<=1;i++)
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
			if(pbp<2)
			{
				strcpy(sam_inf[pbp].cigar, cigar);
				sam_inf[pbp].pos1=pos1;
				sam_inf[pbp].chr=chr_num;
				sam_inf[pbp].flag=flag;
			}
			pbp++;
		}
	}
	free(sam_inf);
}
void BuildList_ins( PosNode **L,  PosNode **tail, unsigned long long int InsPos1)
{
        struct PosNode *temp;
        temp =(struct PosNode *)malloc( sizeof(struct PosNode) );
        temp->pos1 = InsPos1;
        temp->next=NULL;
        if( (*tail)!=NULL )
        {
                temp->next = NULL;
                (*tail)->next = temp;
                temp->prior = (*tail) ;
                *tail = (*tail)->next;
        }
        else
        {
                (*L)->next  = temp;
                temp->prior = (*L);
                *tail=temp;
        }
}

