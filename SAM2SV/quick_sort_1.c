#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include"sam2sv.h"


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

