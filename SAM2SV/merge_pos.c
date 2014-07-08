#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sam2sv.h"
void  merge_pos(struct PosNode **L , int set_pos)
{
	struct PosNode *p;
	p=(*L);
	while( (p->next)!=NULL )
	{
		if( ((p->next->pos1)&0xffffff0000000000)>>40 < set_pos  )
		{
			p=p->next;
			if(p->prior!=NULL)
				p->prior->next=p->next;
			if(p->next!=NULL)
				p->next->prior=p->prior;
			else break;
			free(p);
		}
		else p=p->next;

	}
}
void filer_L( struct PosNode **L , int Area)
{
	struct PosNode *p;
	struct PosNode *q;//traversal list
	struct PosNode *r;//free node
	p=(*L)->next;
	p->prior=(*L);
	unsigned long long int p_pos1;
	unsigned long long int p_pos2;
	while( p )
	{
		q=p;
		p_pos1=p->pos1;
		p_pos2=p->pos2;
		while( q->next && (((q->next->pos1)&0xffffffffff) - (p_pos1&0xffffffffff) <=Area) && (((q->next->pos2)&0xffffffffff) - (p_pos2&0xffffffffff) <=Area) )
		{
			if( ((q->pos1)&0xffffff0000000000) > ((q->next->pos1)&0xffffff0000000000) )
			{
				r=q->next;
				if(r->next!=NULL)
				{	
					q->next=r->next;
					r->next->prior=q;
					free(r);
				}
				else
				{
					q->next=NULL;
					break;
				}
			}
			else
			{
				r=q;
				q=r->next;
				r->prior->next=r->next;
				r->next->prior=r->prior;
				free(r);
			}
		}
		p=p->next;
	}
}
/*
void  merge_pos(struct PosNode **L , int set_pos);
{
	
	struct PosNode *p;
	unsigned long long int chose_pos1;
	unsigned long long int chose_pos2;
	unsigned long long int repeat_cnt;
	p=(*L);


	while(p!=NULL)
	{
		chose_pos1=(p->pos1)&0x3fffffffff;
		chose_pos2=(p->pos2)&0x3fffffffff;
		repeat_cnt=0;
		while( ((p->next)!=NULL) &&  ((p->next->pos1)&0x3fffffffff)==chose_pos1 &&  ((p->next->pos2)&0x3fffffffff)==chose_pos2)
		{
			repeat_cnt++;
			p->next=p->next->next;
			p->next->next->prior=p;
			free(p->next);
		}
		if(repeat_cnt<set_pos)
		{
			p=p->next;
			p->prior->next = p->next;
			p->next->prior = p->prior;
			free(p);
			list=list->next;	
		}
		else
		{
			p->pos1=((repeat_cnt&0xffff)<<40)+p->pos1;
			p->pos2=((repeat_cnt&0xffff)<<40)+p->pos2;
			p=p->next;
		}
	}
	
}*/
