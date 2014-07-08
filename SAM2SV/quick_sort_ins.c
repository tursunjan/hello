#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"sam2sv.h"

PosNode * partion_ins(PosNode *Lhead, PosNode *pstLow, PosNode *Ltail)
{
	//int cnt=0;
	unsigned long long int iTmp1 = 0;
	unsigned long long int pivot1 = 0;
	pivot1 = (pstLow->pos1) & 0xffffffffff ;
	while ( pstLow != Ltail )
	{
		while ( pstLow != Ltail && (((Ltail->pos1)&0x3fffffffff) >= pivot1  ) )
		{
			Ltail = Ltail->prior;
		}
		iTmp1 = pstLow->pos1;
		pstLow->pos1 = Ltail->pos1;
		Ltail->pos1 = iTmp1;
		while ( pstLow != Ltail && (((pstLow->pos1)& 0x3fffffffff)<=pivot1 ) )
		{
			pstLow = pstLow->next;
		}
		iTmp1 = pstLow->pos1;
		pstLow->pos1 = Ltail->pos1;
		Ltail->pos1 = iTmp1;
	}
	return pstLow;
}


void quick_sort_ins( PosNode *Lhead, PosNode *pstLow, PosNode *Ltail)
{
	PosNode *pstTmp = NULL;	
	pstTmp = partion_ins(Lhead, pstLow, Ltail);
	
	if ( pstLow != pstTmp )
	{
		quick_sort_ins(Lhead,pstLow, pstTmp->prior);
	}
	if ( Ltail != pstTmp )
	{
		quick_sort_ins(Lhead, pstTmp->next, Ltail);
	}
}
