#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"sam2sv.h"

void mutation_type( PosNode *L,int Area )
{
        struct PosNode *p;
	struct PosNode *q;
	int label;
	int en_single=0;
	unsigned long long int temp_bp1_pos1,temp_bp1_pos2,temp_bp2_pos1,temp_bp2_pos2;
        p=L->next;
	if(p!=NULL&&(p->next)==NULL )
		print_single_type(en_single,p->pos1,p->pos2);
        while( (p->next)!=NULL )
        {
		unsigned long long int bp1_pos1,bp1_pos2;
		bp1_pos1=p->pos1;
		bp1_pos2=p->pos2;
                if( (bp1_pos1&0x3f00000000) != (bp1_pos2&0x3f00000000) )
		{
			printf("CTX\t%lld\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0xffffff0000000000)>>40,(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,(bp1_pos2&0x3f00000000)>>32,bp1_pos2&0x3fffffff);
			p=p->next;
		}
		else
		{
			en_single=0;
			q=p->next;
			while(q!=NULL && (q->pos1&0x3f00000000)==(bp1_pos1&0x3f00000000) )
			{
				if((q->pos1&0x3f00000000) == (q->pos2&0x3f00000000) )
				{
					if((bp1_pos1&0xffffffff)>(q->pos1&0xffffffff) )
					{	
						temp_bp1_pos1 = q->pos1;
						temp_bp1_pos2 = q->pos2;
						temp_bp2_pos1 = bp1_pos1;
						temp_bp2_pos2 = bp1_pos2;
					}
					else
					{
						temp_bp1_pos1 = bp1_pos1;
                                                temp_bp1_pos2 = bp1_pos2;
						temp_bp2_pos1 = q->pos1;
                                                temp_bp2_pos2 = q->pos2;
					}
					score(&label,Area,temp_bp1_pos1,temp_bp1_pos2,temp_bp2_pos1,temp_bp2_pos2 );
					print_type(label,&en_single,temp_bp1_pos1,temp_bp1_pos2,temp_bp2_pos1,temp_bp2_pos2);
				}
				q=q->next;
			}
			print_single_type(en_single,bp1_pos1,bp1_pos2);
			p=p->next;
		}	
	}
}

void score(int *label ,int Area,unsigned long long int bp1_pos1,unsigned long long int bp1_pos2 ,unsigned long long int bp2_pos1,unsigned long long int bp2_pos2)
{
	(*label)=0;
//	if((bp1_pos1&0xffffffff) < (bp2_pos1&0xffffffff) )  (*label)+=512;
//	if((bp1_pos2&0xffffffff) < (bp2_pos2&0xffffffff) )  (*label)+=256;
	if(bp1_pos1&0xc000000000) (*label)+=128;
	if(bp1_pos2&0xc000000000) (*label)+=64;
	if(bp2_pos1&0xc000000000) (*label)+=32;
	if(bp2_pos2&0xc000000000) (*label)+=16;
	if(abs( (bp2_pos1&0xffffffff) - (bp1_pos1&0xffffffff) )<=Area) (*label)+=8;
	if(abs( (bp2_pos2&0xffffffff) - (bp1_pos1&0xffffffff) )<=Area) (*label)+=4;
	if(abs( (bp2_pos1&0xffffffff) - (bp1_pos2&0xffffffff) )<=Area) (*label)+=2;
	if(abs( (bp2_pos2&0xffffffff) - (bp1_pos2&0xffffffff) )<=Area) (*label)++;
//	return lable;
}

void print_type(int label,int *en_single,unsigned long long int bp1_pos1,unsigned long long int bp1_pos2 ,unsigned long long int bp2_pos1,unsigned long long int bp2_pos2 )
{
        //(*en_single)=0;
        if((label&0xff)==105 || (label&0xff)==153){ (*en_single)=1;
                printf( "TRS1\t%lld\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff,bp2_pos1&0x3fffffff,bp2_pos2&0x3fffffff);
        }
        if((label&0xff)==195 ){ (*en_single)=1;
                	printf( "tandemCNV2\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
        }
        if((label&0xff)==60 || (label&0xff)==202){ (*en_single)=1;
		if(abs((bp1_pos1&0x3fffffff)-(bp1_pos2&0x3fffffff))<=30 )
                	printf( "tandemCNV3\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp2_pos1&0x3fffffff,bp2_pos2&0x3fffffff);
		else	printf( "tandemCNV3\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
        }
        if((label&0xff)==57 || (label&0xff)==201){ (*en_single)=1;
                printf( "INV/TRS4\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
        }
        if((label&0xff)==193){ (*en_single)=1;
                printf( "CNV2\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp2_pos1&0x3fffffff,bp2_pos2&0x3fffffff);
        }
        if( (label&0xff)==145 ){ (*en_single)=1;
                printf( "CNV1\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp2_pos1&0x3fffffff,bp2_pos2&0x3fffffff);
        }
	if((label&0xff)==104 || (label&0xff)==152){ (*en_single)=1;
                printf( "CNV3\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff,bp2_pos2&0x3fffffff);
	}
	if((label&0xff)==200){ (*en_single)=1;
                printf( "CNV4\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff,bp2_pos2&0x3fffffff);
	}
        if((label&0xff)==120  || (label&0xff)==65 || (label&0xff)==56  || (label&0xff)==241 ){ (*en_single)=1;
                printf( "TRS2\t%lld\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff,bp2_pos1&0x3fffffff,bp2_pos2&0x3fffffff);
        }
        if( (label&0xff)==136 || (label&0xff)==216 || (label&0xff)==17 || (label&0xff)==177 ){ (*en_single)=1;
                printf( "TRS3\t%lld\t%lld\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff,bp2_pos1&0x3fffffff,bp2_pos2&0x3fffffff);
        }
}


void print_single_type(int en_single,unsigned long long int bp1_pos1,unsigned long long int bp1_pos2 )
{
        if(!en_single){
                if((bp1_pos2&0xc000000000)==(bp1_pos1&0xc000000000) )
                {
                        if((bp1_pos1&0xc000000000)==0x4000000000)
                                printf( "TRSdl\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
                        else
                                printf( "TRSdR\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
                }
                else
                {
                        if((bp1_pos1&0xc000000000)==0x4000000000)
                                printf( "tandemCNV1\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
                        else
                                printf( "DEL\t%lld\t%lld\t%lld\n",(bp1_pos1&0x3f00000000)>>32,bp1_pos1&0x3fffffff,bp1_pos2&0x3fffffff);
                }
        }
}

