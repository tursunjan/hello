#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "sam2sv.h"

int usage(is_long_help)
{
 	fprintf(stderr,"\n");
 	fprintf(stderr,"SAM2SV\n");
 	fprintf(stderr,"Usage:  SAM2SV [options] in.sam out_abp > out.sv\n");
 	fprintf(stderr,"Options:\n");
	fprintf(stderr,"	-i INT	INS		[       default : 0     ]\n");
	fprintf(stderr,"        -a INT  area		[       default : 30    ]\n");
	fprintf(stderr,"        -s INT  support		[       default : 5     ]\n");
	fprintf(stderr,"        -p INT  set position	[       default : 3     ]\n");
 	fprintf(stderr,"        -m INT  m_gather_size	[	default : 10    ]\n");
	fprintf(stderr,"        -?      longer help\n");
 	fprintf(stderr,"\n");
 	if(is_long_help)
		fprintf(stderr,"Notes: \n\
1. -i1, means to find the INS mutation\n\
2. for more help , the C file can help you \n\
\n");
	return 0;
}

int  main(int argc, char *argv[])
{
	int read_en;
	int c;
	int Area=30;
	int Support=2;
	int set_pos=3;
	int m_gather_size=10;
	int INS=0;
	//int buffer=10000;
	//int Repeat=1;
	int is_long_help=0;
	while ((c = getopt(argc, argv, "p:s:a:m:i:?" )) >= 0) {
		switch(c){
			case 'i': INS		= atoi(optarg);	break;
			case 'p': set_pos	= atoi(optarg)-1; break;
			case 's': Support       = atoi(optarg); break;
			case 'a': Area          = atoi(optarg); break;
			case 'm': m_gather_size	= atoi(optarg); break;
			case '?': is_long_help  = 1; break;
			default : fprintf(stderr,"Unknown option\n");
				usage(is_long_help);
				break;
		}
	}
	if(argc-optind !=2)
		return usage(is_long_help);
	
	FILE *org_abp;
	org_abp = fopen(argv[optind+1],"w");

	FILE *fp;
	fp=fopen( argv[optind],"r");
	for(read_en=0;read_en<86;read_en++)
		fscanf(fp,"%*[^\n]\n");
	struct PosNode *L;
	L =(struct PosNode *)malloc( sizeof(struct PosNode) );
	L->pos1=0;
	L->pos2=0;
	L->next=NULL;
	L->prior=NULL;
	struct PosNode *tail;
	tail =(struct PosNode *)malloc( sizeof(struct PosNode) );
	tail = NULL;
	if(INS==0)
	{
		read_sam(fp, &L, &tail);
//	printf("after read sam\n");	
// 	printList( L );
		quick_sort( L,L->next, tail);
//	printf("after quick_sort\n");
//	printList( L );
		Remove_redundant (&L);
//	printf("after Remove\n");
		fprint_abp( org_abp,L );

		gather_L(&L ,m_gather_size,set_pos);
//	printf("after gather\n");
//	printList( L );	
		merge_pos(&L , Support);
//	printf("after merge\n");
//	printList( L );
		filer_L( &L , Area);
//	printf("after filer_L\n");
//	printList( L );
		print_abp(L );
//		mutation_type( L ,Area);
	}
	else
	{
		read_sam_ins(fp, &L, &tail);
//	printf("after read sam\n");
 //	printList( L );
		quick_sort( L,L->next, tail);
//	printf("after quick_sort\n");
//     printList( L );
		Remove_redundant (&L);
		fprint_abp( org_abp ,L );
//	printf("after Remove\n");
  //    printList( L );
		gather_L(&L ,m_gather_size,set_pos);
//	printf("after gather\n");
 //     printList( L );
		merge_pos(&L , Support);
//	 printf("after merge\n");
 //     printList( L );
		filer_L( &L , Area);
//	printf("after filer_L\n");
//      printList( L );
		print_abp(L );
//		mutation_type_ins( L ,Area);
	}
	fclose(fp);
	return 0;
}
