#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
	
int chr2num (char chr[20])
{
        int num;
        int c=strlen(chr);
        if(c==4)
        {
                switch( chr[3] )
                {
                        case 'M' :  num=23; break;
                        case 'X' :  num=24; break;
                        case 'Y' :  num=25; break;
                        default  :  num=chr[3]-48; break;
                }
        }
        else if(c==5)
        {
                num = (chr[3]-48)*10 + chr[4]-48;
        }
        else num =0;
        return num;
}

struct sam{
        char cigar[100];
        int flag;
        int pos1;
        int chr;
};

int  main(int argc, char *argv[])
{
	if(argc!=4)
        {
                printf("usage: ./read_sam_depth sam.file abp depth_abp \n ");
                return 0;
        }
	struct sam *sam_inf=(struct sam*)malloc(10*sizeof(struct sam));
	int i,pbp, flag, pos1, pos2, chr_num , flag_reg=0;
	int cnt=0;
	int abp_pos,abp;
	char abp_name[10];
	int h_ins_num,t_ins_num,h_num,t_num;
	char abp_chr[20];

	char cigar[100],chr[20];
	
	FILE *fp_w;
	fp_w=fopen( argv[3],"w");

	FILE *fp_abp;
	fp_abp=fopen(argv[2],"r" );
	while(!feof(fp_abp))
	{
		fscanf(fp_abp, "%s\t%s\t%d\t%d\t%d\t%d\t%d\n", abp_name,abp_chr,&abp_pos,&h_ins_num,&t_ins_num,&h_num,&t_num);
		cnt=0;
		FILE *fp;
		fp=fopen( argv[1],"r");
		fscanf(fp,"%*[^\n]\n");
		fscanf(fp,"%*[^\n]\n");
		while(!feof(fp))
		{
			fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
			while(strcmp(cigar,"*")==0)
			{	
				fscanf(fp, "%*[^\t]\t%d\t%[^\t]\t%d\t%*[^\t]\t%[^\t]\t%*[^\n]\n", &flag,chr,&pos1,cigar);
			}
			chr_num=chr2num(chr);		// change the chrom to num , in order to save conveniently	
			if((flag&0xc0)!=(flag_reg&0xc0))
			{
				if(pbp == 1)
				{
					if(strcmp(sam_inf[0].cigar,"100M")==0)
					{
						if( abp_pos>sam_inf[0].pos1 && abp_pos < (sam_inf[0].pos1+100))
						cnt++;
					}
				}
				pbp=0;
				strcpy(sam_inf[pbp].cigar, cigar);
				flag_reg=flag;
       	                	sam_inf[pbp].pos1=pos1;
				sam_inf[pbp].flag=flag;
	                        sam_inf[pbp].chr=chr_num;
       	               	 	pbp++;			
			}
			else
			{
				pbp++;
			}
		}
		fprintf(fp_w,"%d\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n",cnt,abp_name,abp_chr,abp_pos,cnt+h_ins_num+t_ins_num+h_num+t_num ,h_ins_num,t_ins_num,h_num,t_num);
		fclose(fp);
	}
	fclose(fp_abp);
	free(sam_inf);
}

