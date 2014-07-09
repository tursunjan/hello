#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
//list.c
unsigned long long int  bp_pos1,bp_pos2;
//sort_list.c
/*
unsigned long long int bp[2];
unsigned long long int ht[2];
unsigned long long int bp_reg;
unsigned long long int ht_reg;
unsigned long long int chr_reg;
*/
struct strce{
	char cigar[200];
	int flag; 
	unsigned long long int pos;
	int  sw_score;
	unsigned long long int chr;
};

struct strbi{
	unsigned long long int pos[2]; 
	int support;
	unsigned long long int ht[2]; //0H 1T
};

struct strpa{
	char name[20];
	unsigned long long int bp[4];
	int support;
};

typedef struct PosNode{
        unsigned long long int pos1;
	unsigned long long int pos2;
	struct PosNode *prior;
        struct PosNode *next;
}PosNode;

struct sam{
        char cigar[200];
	int flag; 
        unsigned long int pos1;
	unsigned long long int chr;
};



int chr2num (char chr[20]);
void printList( PosNode *L );
void printList_tail( PosNode *tail );

//void ListInsert( struct PosNode **L, struct PosNode **tail, unsigned long long int InsPos1,unsigned long long int InsPos2 );
void BuildList( struct PosNode **L, struct PosNode **tail, unsigned long long int InsPos1,unsigned long long int InsPos2 );  
void read_sam(FILE *fp, struct PosNode **L,  struct PosNode **tail);
//void sort_list(struct strce *strcell, unsigned long long int *InsPos1, unsigned long long int *InsPos2);
void sure_bp(unsigned long long int pos, int flag ,char *cigar, unsigned long long int *bp, unsigned long long int *ht);

void  merge_pos(struct PosNode **L , int set_pos);

void mutation_type( PosNode *L ,int Area);
void score(int *label ,int Area ,unsigned long long int bp1_pos1,unsigned long long int bp1_pos2 ,unsigned long long int bp2_pos1,unsigned long long int bp2_pos2);
void print_type(int label,int *en_single,unsigned long long int bp1_pos1,unsigned long long int bp1_pos2 ,unsigned long long int bp2_pos1,unsigned long long int bp2_pos2 );
void print_single_type(int en_single,unsigned long long int bp1_pos1,unsigned long long int bp1_pos2 );
void filer_L( struct PosNode **L , int Area);

void quick_sort( PosNode *Lhead, PosNode *pstLow, PosNode *Ltail);
PosNode * partion(PosNode *Lhead, PosNode *pstLow, PosNode *Ltail);

void  Remove_redundant (struct PosNode **L);
void gather_L( struct PosNode **L , int m_gather_size, int set_pos);

void read_sam_ins(FILE *fp, struct PosNode **L, struct PosNode **tail);
void BuildList_ins( PosNode **L,  PosNode **tail, unsigned long long int InsPos1);
void quick_sort_ins( PosNode *Lhead, PosNode *pstLow, PosNode *Ltail);
PosNode * partion_ins(PosNode *Lhead, PosNode *pstLow, PosNode *Ltail);
void  Remove_redundant_ins (struct PosNode **L );
void gather_L_ins( struct PosNode **L , int m_gather_size, int set_pos);
void filer_L_ins( struct PosNode **L , int Area);
void mutation_type_ins( PosNode *L ,int Area);


