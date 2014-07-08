#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sam2sv.h"
void  Remove_redundant (struct PosNode **L )
{
	struct PosNode *p;
	p=(*L);
	while( (p->next)!=NULL )
	{
		if( ((p->next->pos1&0xffffffffff)!=(p->pos1&0xffffffffff)) || ((p->next->pos2&0xffffffffff)!=(p->pos2&0xffffffffff)) )
			p=p->next;
		else
		{
			p->pos1 = p->pos1 + 0x10000000000;
			p->pos2 = p->pos2 + 0x10000000000;
			
			p->next=p->next->next;
			if(p->next!=NULL)
				p->next->prior=p;
		}
	}
}
void gather_L( struct PosNode **L , int m_gather_size, int set_pos)
{
	int shan_en=0;
	struct PosNode *p;
	struct PosNode *q;
	struct PosNode *r;
	p=(*L);
	unsigned long long int p_pos1;
	unsigned long long int p_pos2;
	while(( p->next )!=NULL)
	{
		if(( ((p->next->pos1)&0xffffff0000000000)>>40) < set_pos )
		{
			p=p->next;
		}
		else
		{
			p_pos1=p->next->pos1;
			p_pos2=p->next->pos2;
			q=p->next;
	shan_en=0;
			while((q->next)!=NULL)
			{
			//	if(shan_en)
			//		printf("pos1: %lld\t%lld<10 ?\n", (q->next->pos1)&0xffffffff,(p_pos1&0xffffffff));
				if((((q->next->pos1)&0xffffffffff)-(p_pos1&0xffffffffff)<=m_gather_size))
				{
					shan_en=1;
			//		printf("before: %lld\t%lld\t%lld\n",(p_pos1&0xffffff0000000000)>>40,p_pos1&0xffffffff,p_pos2&0xffffffff);
			//		printf("%lld\t%lld<10 ?\n", (q->next->pos2)&0xffffffff,(p_pos2&0xffffffff));
					if (abs( ((q->next->pos2)&0xffffffffff)-(p_pos2&0xffffffffff))<=m_gather_size)
					{
						r=q->next;
						p_pos1=p_pos1+((q->next->pos1)&0xffffff0000000000)+0x10000000000;
						p_pos2=p_pos2+((q->next->pos1)&0xffffff0000000000)+0x10000000000;
			//			printf("after: %lld\t%lld\t%lld\n",(p_pos1&0xffffff0000000000)>>40,p_pos1&0xffffffff,p_pos2&0xffffffff);
						if((r->next)!=NULL)
						{
							r->prior->next=r->next;
							r->next->prior=r->prior;
						}
						else	q->next=NULL;
						free(r);							
					}
					else q=q->next;
				}	 
				else
					break; 
			}
			p->next->pos1=p_pos1;
			p->next->pos2=p_pos2;
			p=p->next;
		}
	}	
}

