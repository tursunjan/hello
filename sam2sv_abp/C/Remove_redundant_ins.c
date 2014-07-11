#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sam2sv.h"
void  Remove_redundant_ins (struct PosNode **L )
{
	struct PosNode *p;
	p=(*L);
	while( (p->next)!=NULL )
	{
		if( ((p->next->pos1&0xffffffffff)!=(p->pos1&0xffffffffff))  )
			p=p->next;
		else
		{
			p->pos1 = p->pos1 + 0x10000000000;
			p->next=p->next->next;
			if(p->next!=NULL)
				p->next->prior=p;
		}
	}
}
void gather_L_ins( struct PosNode **L , int m_gather_size, int set_pos)
{
	int shan_en=0;
	struct PosNode *p;
	struct PosNode *q;
	struct PosNode *r;
	p=(*L);
	unsigned long long int p_pos1;
	while(( p->next )!=NULL)
	{
		if(( ((p->next->pos1)&0xffffff0000000000)>>40) < set_pos )
		{
			p=p->next;
		}
		else
		{
			p_pos1=p->next->pos1;
			q=p->next;
	shan_en=0;
			while((q->next)!=NULL)
			{
				if((((q->next->pos1)&0xffffffffff)-(p_pos1&0xffffffffff)<=m_gather_size))
				{
					shan_en=1;
						r=q->next;
						p_pos1=p_pos1+((q->next->pos1)&0xffffff0000000000)+0x10000000000;
						if((r->next)!=NULL)
						{
							r->prior->next=r->next;
							r->next->prior=r->prior;
						}
						else	q->next=NULL;
						free(r);							
				}	 
				else
					break; 
			}
			p->next->pos1=p_pos1;
			p=p->next;
		}
	}	
}

