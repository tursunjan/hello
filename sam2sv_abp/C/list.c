#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"sam2sv.h"

void BuildList( PosNode **L,  PosNode **tail, unsigned long long int InsPos1,unsigned long long int InsPos2 )
{
	struct PosNode *temp;
	temp =(struct PosNode *)malloc( sizeof(struct PosNode) );
	temp->pos1 = InsPos1;
	temp->pos2 = InsPos2;
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

void fprint_abp(FILE *org_abp,PosNode *L)
{
	struct PosNode *p;
	p=L->next;
	if(NULL == p)
	{
		printf(" List is NULL\n");
	}
	else
	{
		while(NULL != p)
                {
			if( (p->pos1)&0xc000000000 )
				fprintf(org_abp,"T\t");
			else	fprintf(org_abp,"H\t");
                        fprintf(org_abp,"chr%lld\t%lld\t%lld\t%lld\n",((p->pos1)&0x3f00000000)>>32,(p->pos1)&0x3fffffff,((p->pos1)&0xffffff0000000000)>>40,((p->pos2)&0xffffff0000000000)>>40 );
                        p = p->next;
                }
	}
}

//print list
void print_abp(PosNode *L )
{
	struct PosNode *p;
	p=L->next;
	if(NULL == p)
	{
		printf(" List is NULL\n");
	}
	else
	{
		while(NULL != p)
		{
			if(((p->pos1)&0xffffff0000000000)!=0 && ((p->pos2)&0xffffff0000000000)!=0)
				printf("H/T\t");
			else if( ((p->pos1)&0xffffff0000000000)!=0)
				printf("H\t");
			else printf("T\t");
			
			printf("chr%lld\t%lld\t%lld\t%lld\n",((p->pos1)&0x3f00000000)>>32,(p->pos1)&0x3fffffff,((p->pos1)&0xffffff0000000000)>>40,((p->pos2)&0xffffff0000000000)>>40 );
			p = p->next;
		}
	//	printf("\n");
	}
}
void printList( PosNode *L )
{
	struct PosNode *p;
	p=L;
	
	if(NULL == p)   //链表为空
	{
		printf("PrintList run , and List is NULL\n");
	}
	else
	{	
		while(NULL != p)
		{
			printf("%lld\t%lld\tchr%lld\t%lld\t%lld\tchr%lld\t%lld\t%lld\n ",((p->pos1)&0xff0000000000)>>40,((p->pos2)&0xff0000000000)>>40,((p->pos1)&0x3f00000000)>>32,(p->pos1)&0x3fffffff,((p->pos1)&0xc000000000)>>38,((p->pos2)&0x3f00000000)>>32,(p->pos2)&0x3fffffff,((p->pos2)&0xc000000000)>>38  );
			p = p->next;
		}
		printf("\n");
	}
}

void printList_tail( PosNode *tail )
{
        struct PosNode *p;
        p=tail;

        if(NULL == p)   //链表为空
        {
                printf("PrintList run , and List is NULL\n");
        }
        else
        {
                while(NULL != p)
                {
                        printf("%lld\t%lld\tchr%lld\t%lld\t%lld\tchr%lld\t%lld\t%lld\n ",((p->pos1)&0xff0000000000)>>40,((p->pos2)&0xff0000000000)>>40,((p->pos1)&0x3f00000000)>>32,(p->pos1)&0x3fffffff,((p->pos1)&0xc000000000)>>38,((p->pos2)&0x3f00000000)>>32,(p->pos2)&0x3fffffff,((p->pos2)&0xc000000000)>>38  );
                        p = p->prior;
                }
                printf("\n");
        }
}

