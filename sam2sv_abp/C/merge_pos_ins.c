#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sam2sv.h"
void filer_L_ins( struct PosNode **L , int Area)
{
	struct PosNode *p;
	struct PosNode *q;//traversal list
	struct PosNode *r;//free node
	p=(*L)->next;
	p->prior=(*L);
	unsigned long long int p_pos1;
	while( p )
	{
		q=p;
		p_pos1=p->pos1;
		while( q->next && (((q->next->pos1)&0xffffffffff) - (p_pos1&0xffffffffff) <=Area)  )
		{
			if( ((q->pos1)&0xff0000000000) > ((q->next->pos1)&0xff0000000000) )
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
void mutation_type_ins( PosNode *L ,int Area)
{
        struct PosNode *p;
        p=L->next;

        if(NULL == p)   //链表为空
        {
                printf("PrintList run , and List is NULL\n");
        }
        else
        {
                while(NULL != p)
                {
                        printf( "INS\tchr%lld\t%lld\t%lld\n",((p->pos1)&0x3f00000000)>>32, (p->pos1)&0x3fffffff,(p->pos1)&0x3fffffff);
                        p = p->next;
                }
                printf("\n");
        }
}









