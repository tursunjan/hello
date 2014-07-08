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
//		(*L)=temp;
//		temp->prior = NULL;
//		*tail=temp;
		(*L)->next  = temp;
		temp->prior = (*L);
		*tail=temp;
	}
}
/*
PosNode * partion(PosNode **L, PosNode **pstLow, PosNode **tail)
{
        unsigned long long int iTmp1 = 0;
	unsigned long long int iTmp2 = 0;
        unsigned long long int pivot = 0;
        if ( !(*L) )
        {
                printf("错误，头节点为空！/n");
                exit(1);
        }
        if ( !((*L)->next) )
        {
                return (*L)->next;//就一个元素
        }

        pivot = ((*pstLow)->pos1) & 0x3fffffffff ;
        while ( (*pstLow) != *tail )
        {
//从后面往前换
                while ( (*pstLow) != (*tail) && (((*tail)->pos1)&0x3fffffffff) >= pivot )
                {
                        (*tail) = (*tail)->prior;
                }
//交换high low
                iTmp1 = (*pstLow)->pos1;
		iTmp2 = (*pstLow)->pos2;
                (*pstLow)->pos1 = (*tail)->pos1;
		(*pstLow)->pos2 = (*tail)->pos2;
                (*tail)->pos1 = iTmp1;
		(*tail)->pos2 = iTmp2;
//从前往后换
                while ( (*pstLow) != (*tail) && (((*pstLow)->pos1)& 0x3fffffffff) <= pivot )
                {
                        (*pstLow) = (*pstLow)->next;
                }
//交换high low
                iTmp1 = (*pstLow)->pos1;
		iTmp2 = (*pstLow)->pos2;
                (*pstLow)->pos1 = (*tail)->pos1;
		(*pstLow)->pos2 = (*tail)->pos2;
                (*tail)->pos1 = iTmp1;
		(*tail)->pos2 = iTmp2;
        }
        return *pstLow;
}

void quick_sort( PosNode **L, PosNode **pstLow, PosNode **tail)
{
        PosNode *pstTmp = NULL;
        pstTmp = partion(&(*L), &(*pstLow), &(*tail));
        if ( *pstLow != pstTmp )
        {
		quick_sort(&(*L),&(*pstLow), &(pstTmp->prior));
        }
        if ( *L != pstTmp )
        {
		quick_sort(&(*L), &(pstTmp->next), &(*tail));
        }

}
*/
/*

void ListInsert( PosNode **L, unsigned long long int InsPos1,unsigned long long int InsPos2 )
{
	struct PosNode *temp;
	struct PosNode *p;
	p=(*L)->next;
//	if(p != NULL)
//		p->prior = (*L);

	temp =(struct PosNode *)malloc( sizeof(struct PosNode) );
	temp->pos1 = InsPos1+0x10000000000;
	temp->pos2 = InsPos2+0x10000000000;
	temp->next = NULL;
	temp->prior = NULL;
	bp_pos1 = InsPos1&0x3fffffffff;//chrom and pos num  , chr_pos  ,
	bp_pos2 = InsPos2&0x3fffffffff;//chrom is 6 bit , and at  position 38-32 ; pos is 32 bit , at position 32-0 
	if(p == NULL)
	{
		temp->prior = (*L);
		(*L)->next  = temp;
	}
	else if (( (p->pos1) & 0x3fffffffff) ==  bp_pos1 && ( (p->pos2) & 0x3fffffffff) ==  bp_pos2)
	{
		p->pos1 = p->pos1 + 0x10000000000;
		p->pos2 = p->pos2 + 0x10000000000;
	}
	else if( ( (p->pos1) & 0x3fffffffff) > bp_pos1) //pre pos ins
	{
		temp->prior=(*L);(*L)->next=temp;
		p->prior=temp;temp->next=p;
	//	temp->prior = p->prior; p->prior->next=temp;
	//	temp->next = p; p->prior=temp;		
	}
	else if( p->next!=NULL )
	{	
		while( (p->next!=NULL) && ( ( (p->next->pos1)  & 0x3fffffffff) < bp_pos1) )
		{
			 p = p->next;
		}
		if( p->next==NULL )
		{
			p->next=temp;
			temp->prior=p;
		}
		else if(( (p->next->pos1) & 0x3fffffffff) ==  bp_pos1 && ( (p->next->pos2) & 0x3fffffffff) ==  bp_pos2)
		{
			p->next->pos1 = p->next->pos1 + 0x10000000000;
			p->next->pos2 = p->next->pos2 + 0x10000000000;
		}
		else
		{
			temp->next=p->next; p->next->prior=temp;
			p->next=temp;temp->prior=p;
		}
	}
}
*/
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

/*
main ()
{
	int i, j ;
        int temp1;
        int n=0;
        int m=0;
        int num[4];

	struct PosNode *L;
	L =(struct PosNode *)malloc( sizeof(struct PosNode) );
	L->pos=2;
        L->next=NULL;

//	PosNode *L=NULL;
//	initList(&L);
        long long data64;
        for(i=1;i<5;i++)
        {
                for(j=1;j<2;j++)
                {
                        data64=i;
                        data64=data64<<1;
                        data64+=n;
                        data64=data64<<32;
                        temp1=j;
                        temp1=temp1<<1;
                        temp1+=m;
                        data64+=temp1;
                        temp1=0;
			ListInsert( &L, data64 );
                }
        }
	for(i=10;i>5;i--)
        {
                for(j=1;j<2;j++)
                {
                        data64=i;
                        data64=data64<<1;
                        data64+=n;
                        data64=data64<<32;
                        temp1=j;
                        temp1=temp1<<1;
                        temp1+=m;
                        data64+=temp1;
                        temp1=0;
                        ListInsert( &L, data64 );
                }
        }
	
	

	printList( L );
	
}*/
