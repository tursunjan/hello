#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "sam2sv.h"
	
void read_sam(FILE *fp, struct PosNode **L){
	struct strce *strcell=(struct strce*)malloc(10*sizeof(struct strce));
	char name[50], cigar[20], name_reg[50],chr[20];
	int i;
	struct sam *sam_inf=(struct sam*)malloc(100*sizeof(struct sam));
	int pbp, flag, pos1, pos2, sw_score;
	
	unsigned long long int InsPos1=0;
        unsigned long long int InsPos2=0;
	
/*	struct PosNode *L;
	L =(struct PosNode *)malloc( sizeof(struct PosNode) );	
	L->pos1=0;
	L->pos2=0;
	L->next=NULL;
	L->prior=NULL;
*/	
	int chr_num;
	
	pbp=0;
	while(!feof(fp)){
		fscanf(fp, "%[^\t]\t%d\t%[^\t]\t%d\t%d\t%[^\t]\t%*[^\t]\t%d\t%*[^\n]\n", name, &flag,chr, &pos1, &sw_score, cigar,&pos2);
		while(strcmp(cigar,"*")==0)
			fscanf(fp, "%[^\t]\t%d\t%[^\t]\t%d\t%d\t%[^\t]\t%*[^\t]\t%d\t%*[^\n]\n", name, &flag,chr, &pos1, &sw_score, cigar,&pos2);
		chr_num=chr2num(chr);	// change the chrom to num , in order to save conveniently	

		if(strcmp(name, name_reg)){
			if(pbp==3 && pbp > 2){
				if( sam_inf[0].pos1==sam_inf[1].pos2 && sam_inf[0].pos1==sam_inf[2].pos2 )
				{
					strcpy( strcell[0].cigar, sam_inf[1].cigar );
					strcell[0].flag = sam_inf[1].flag;
					strcell[0].pos = sam_inf[1].pos1;
					strcell[0].sw_score = sam_inf[1].sw_score;
					strcell[0].chr=sam_inf[1].chr;
					
					strcpy( strcell[1].cigar, sam_inf[2].cigar );
					strcell[1].flag = sam_inf[2].flag;
					strcell[1].pos = sam_inf[2].pos1;
					strcell[1].sw_score = sam_inf[2].sw_score;
					strcell[1].chr=sam_inf[2].chr;
				
					sort_list(strcell,&InsPos1 ,&InsPos2);
					ListInsert( &(*L), InsPos1, InsPos2 );
				}
				else if( sam_inf[1].pos1==sam_inf[0].pos2 && sam_inf[1].pos1==sam_inf[2].pos2 )
				{
					strcpy( strcell[0].cigar, sam_inf[0].cigar );
					strcell[0].flag = sam_inf[0].flag;
					strcell[0].pos = sam_inf[0].pos1;
					strcell[0].sw_score = sam_inf[0].sw_score;
					strcell[0].chr=sam_inf[0].chr;
					
					strcpy( strcell[1].cigar, sam_inf[2].cigar );
					strcell[1].flag = sam_inf[2].flag;
					strcell[1].pos = sam_inf[2].pos1;
					strcell[1].sw_score = sam_inf[2].sw_score;
					strcell[1].chr=sam_inf[2].chr;
					
					sort_list(strcell,&InsPos1 ,&InsPos2);
                                        ListInsert( &(*L), InsPos1, InsPos2 );
				}
				else if(  sam_inf[2].pos1==sam_inf[0].pos2 && sam_inf[2].pos1==sam_inf[1].pos2 )
				{
					strcpy( strcell[0].cigar, sam_inf[0].cigar );
					strcell[0].flag = sam_inf[0].flag;
					strcell[0].pos = sam_inf[0].pos1;
					strcell[0].sw_score = sam_inf[0].sw_score;
					strcell[0].chr=sam_inf[0].chr;
					
					strcpy( strcell[1].cigar, sam_inf[1].cigar );
					strcell[1].flag = sam_inf[1].flag;
					strcell[1].pos = sam_inf[1].pos1;
					strcell[1].sw_score = sam_inf[1].sw_score;
					strcell[1].chr=sam_inf[1].chr;
					
					sort_list(strcell,&InsPos1 ,&InsPos2);
                                        ListInsert( &(*L), InsPos1, InsPos2 );
				} 	
				//ent_bpinf(strbpinf, bpinfnum, strcell, Area, pbp);
			}
			for(i=0;i<=pbp;i++)
			{
				memset(sam_inf[pbp].cigar,20,0);
				sam_inf[pbp].flag=0;
				sam_inf[pbp].pos1=0;
				sam_inf[pbp].sw_score=0;
				sam_inf[1].chr=0;
			}
			strcpy(name_reg, name);
			pbp=0;
			strcpy(sam_inf[pbp].cigar, cigar);
			sam_inf[pbp].flag=flag;
			sam_inf[pbp].pos1=pos1;
			sam_inf[pbp].pos2=pos2;
			sam_inf[pbp].sw_score=sw_score;
			sam_inf[pbp].chr=chr_num;
			pbp++;
		}else{
			strcpy(sam_inf[pbp].cigar, cigar);
			sam_inf[pbp].flag=flag;
			sam_inf[pbp].pos1=pos1;
			sam_inf[pbp].pos2=pos2;
			sam_inf[pbp].sw_score=sw_score;
			sam_inf[pbp].chr=chr_num;
			pbp++;
		}
	}
//	printList( L );
	free(strcell);
//fclose(fp);
}

