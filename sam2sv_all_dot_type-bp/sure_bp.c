#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

void sure_bp(int pos, char *cigar, int *bp, int *ht){
	int cnt, n, bit;
	int en_i=0 ; //20M1D20M59S  D or I bwteen 2 M,
	
	char charnum[4];
	int num[4], type[4];
	strcpy(charnum, "0000");
	n=0;
	bit=0;
	num[0]=0; num[1]=0; num[2]=0; num[3]=0;
	type[0]=0; type[1]=0; type[2]=0; type[3]=0;
	for(cnt=0;cnt<=strlen(cigar)-1;cnt++){
		if(cigar[cnt]=='S' || cigar[cnt]=='H'){
			charnum[bit]='\0';
			num[n]=atoi(charnum);
			type[n]=0;
			strcpy(charnum, "0000");
			bit=0;
			n++;
		}else if(cigar[cnt]=='M'){
			charnum[bit]='\0';
			if(en_i){
			        n--;
			        num[n]+=atoi(charnum);
			}else
			        num[n]=atoi(charnum);
			en_i=0;
			type[n]=1;
			strcpy(charnum, "0000");
			bit=0 ;
			n++;
		}
		else if(cigar[cnt]=='I' ||  cigar[cnt]=='D'){
			charnum[bit]='\0';
			n--;
			num[n]+=atoi(charnum);
			strcpy(charnum, "0000");
			bit=0;
			n++;
			en_i=1;
		}
		else{
			charnum[bit]=cigar[cnt];
			bit++;
		}
	}
/*	if(flag & 0x0010)
	{
		if((type[0]==1&&type[2]==0) || (type[0]==1 && type[2]==1 && num[0]>=num[2])  )//50M50S OR 62M30S8M
                {
                        *ht=0;
                        *bp=pos-1;
                }
                else if( type[0]==0 && num[0]<=num[2] )
                {                                       // H 2S30M68S
                        *ht=0;
                        *bp=pos-1;
                } else if ( type[0]==1 && type[2]==1 && num[0]<num[2] )
                {                                       // 2M30S68M
                        *ht=1;
                        *bp=pos+num[1];
                }
                else{                                   // 70S70M  68S30M2S
                        *ht=1;
                        *bp=pos+num[0];
                }
	}
	else
	{*/
		if((type[0]==1&&type[2]==0) || (type[0]==1 && type[2]==1 && num[0]>=num[2])  )//50M50S OR 62M30S8M
		{
                        *ht=0;
                        *bp=pos+num[0];
                }
                else if( type[0]==0 && num[0]<=num[2] )
		{ 					// H 2S30M68S
                        *ht=0;
                        *bp=pos+num[1];
                } else if ( type[0]==1 && type[2]==1 && num[0]<num[2] )
		{					// 2M30S68M
                        *ht=1;
                        *bp=pos-1;
                }
		else{  					// 70S70M  68S30M2S
			*ht=1;
			*bp=pos-1;
		}
//	}
}


