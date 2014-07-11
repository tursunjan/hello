#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"sam2sv.h"

PosNode * partion(PosNode *Lhead, PosNode *pstLow, PosNode *Ltail)
{
	//int cnt=0;
	unsigned long long int iTmp1 = 0;
//	unsigned long long int iTmp2 = 0;
	unsigned long long int pivot1 = 0;
	unsigned long long int pivot2 = 0;
/*	if ( !Lhead )	
	{
		printf("错误，头节点为空！/n");
		exit(1);
	}
	if ( !(Lhead->next) )
	{
		return Lhead->next;//就一个元素
	}
*/
	pivot1 = (pstLow->pos1) & 0xffffffffff ;
	pivot2 = (pstLow->pos2) & 0xffffffffff ;
	while ( pstLow != Ltail )
	{
	//	printf("%d\t%lld\t%lld\n ",cnt++,Ltail->pos1&0xffffffff , Ltail->pos2&0xffffffff);
		
//从后面往前换
		//printf("test\n");
		//printList( Lhead );
		//printf("test1 %lld\t%lld\t%lld\n",Lhead->pos1&0xffffffff,pstLow->pos1&0xffffffff, (Ltail->pos1)&0xffffffff);
		while ( pstLow != Ltail && (((Ltail->pos1)&0xffffffffff) >= pivot1 ))//|| ( ((Ltail->pos1)&0x3fffffffff) == pivot1  && ((Ltail->pos2)&0x3fffffffff) >= pivot2 ) ))
		{
			Ltail = Ltail->prior;
		}
//交换high low	
		iTmp1 = pstLow->pos1;
		pstLow->pos1 = Ltail->pos1;
		Ltail->pos1 = iTmp1;
		
//从前往后换
		while ( pstLow != Ltail && (((pstLow->pos1)& 0xffffffffff) <= pivot1 ))// ||(((pstLow->pos1)& 0x3fffffffff)==pivot1&&((pstLow->pos2)&0x3fffffffff)<=pivot2 ) ) )
		{
			pstLow = pstLow->next;
		}
//交换high low
		iTmp1 = pstLow->pos1;
		pstLow->pos1 = Ltail->pos1;
		Ltail->pos1 = iTmp1;
		
	}
	return pstLow;
}


void quick_sort( PosNode *Lhead, PosNode *pstLow, PosNode *Ltail)
{
	PosNode *pstTmp = NULL;	
	pstTmp = partion(Lhead, pstLow, Ltail);
	
	//printf ("%lld\t%lld\n",pstTmp->pos1&0xffffffff,pstTmp->pos2&0xffffffff);
//	printf("L\n");
//	printList( Lhead );
	if ( pstLow != pstTmp )
	{
		quick_sort(Lhead,pstLow, pstTmp->prior);
	}
	if ( Ltail != pstTmp )
	{
		quick_sort(Lhead, pstTmp->next, Ltail);
	}
//	printf("ok2\n");
//	printf("quick_sort\n");
//	printList( Lhead );
}
