#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <math.h>

#define total_feature 201
#define total_row 160001
#define copies 1000
#define speed 10
#define super_min -1000

#define SPE_incremental 0.01
#define SPE_reduction 0.01
#define FMEAS_incremental 0.01
#define FMEAS_reduction 0.01

struct fea
{
	char name[20];
	char symbol[20];
	int rule;
};

struct fea feature_file[total_feature];

struct matrix
{
	char name[20];
};
struct matrix matrix_file[total_feature];

main(int argc,char *argv[])
{
	char name[20],ch;
	FILE *fp;
	int m_num,seed_one,seed_another,
			col,row,file_col,file_row,feature_num,
			which_row[total_feature],which_col[total_feature],en[total_feature],seed[total_feature],en_seed,feature_which,new_seed,have_this,feauture_unit,
			incremental_one,incremental_another,
			TP[total_feature],FP[total_feature],TN[total_feature],FN[total_feature],
			TP_reg[total_feature],FP_reg[total_feature],TN_reg[total_feature],FN_reg[total_feature],
			better_one,better_another,best_one,best_another,
			best_TP,best_FP,best_FN,best_TN;
	
	float SEN[total_feature],PREC[total_feature],SPE[total_feature],FMEAS[total_feature],
				SEN_reg[total_feature],PREC_reg[total_feature],FMEAS_reg[total_feature],SPE_reg[total_feature],
				best_SEN,best_PREC,best_SPE,best_FMEAS,
				feature_one,feature_another,better_feature_one,better_feature_another,
				feature_detail[total_feature],feature_detail_reg[total_feature],best_feature_detail,
				min[total_feature],max[total_feature],stp[total_feature];
//	float file_mat[total_row][total_feature];
	float **file_mat ;

//star	
	if(argc!=4)
	{
		printf("\nERROR\n"
					 "1:Feature file\n"
					 "2:Matrix file\n"
					 "3:Detailed results file\n\n");
		return(0);
	}
	else
	{
		printf("\nSUCESS\n"
					 "<feature file>:%s\n"
					 "<Matrix file>:%s\n"
					 "<Detailed results file>:%s\n\n"
					 ,argv[1],argv[2],argv[3]);
	}
	printf("Version:07201030 <SPE && FMEAS> <100 find seed> <1000 arrangement>\n");
	file_mat =  malloc(total_row*sizeof(float*));
	int  ti =  0 ;
	for(   ;  ti <  total_row ;  ti++)
		file_mat[ti] = malloc(sizeof(float)*total_feature);
	
	int compare(int en,float feature_detail,float matrix_value,int rule);
//rst	
	for(m_num=0;m_num<=total_feature-1;m_num++)
	{	
		which_row[m_num]=-1;
		seed[m_num]=0;
		min[m_num]=0;
		max[m_num]=0;
		stp[m_num]=1;
		feature_detail[m_num]=0;
		feature_detail_reg[m_num]=0;
	}
//read feature	
	fp=fopen(argv[1],"r");
	row=0;
	while(!feof(fp))
	{
		fscanf(fp,"%s\t%d\n",feature_file[row].name,&feature_file[row].rule);
		row++;
	}
	feature_num=row-1;	//feature num
	fclose(fp);
//read mat col
	fp=fopen(argv[2],"r");
	col=0;
	while((ch=fgetc(fp))!='\n')
	{
		if(ch=='\t')
			col++;
	}
	file_col=col+1; //file col
	fclose(fp);	
//read mat row	
	fp=fopen(argv[2],"r");
	for(col=1;col<=file_col;col++)
	{
		fscanf(fp,"%s\t",name);
		strcpy(matrix_file[col].name,name);
		for(row=0;row<=feature_num;row++)
		{
			if(strcmp(feature_file[row].name,name)==0)
			{
				which_row[col]=row;
				which_col[row]=col;
				break;
			}
		}
	}
	
	row=0;
	while(!feof(fp))
	{
		row++;
		for(col=1;col<=file_col;col++)
		{
			fscanf(fp,"%s\t",name);
			if(which_row[col]!=-1)
			{
				file_mat[row][which_row[col]]=atof(name);
				if(row==1)
				{
					min[which_row[col]]=atof(name);
					max[which_row[col]]=atof(name);
				}
				else if(atof(name)<min[which_row[col]]&&atof(name)>super_min)
					min[which_row[col]]=atof(name);
				else if(atof(name)>max[which_row[col]])
					max[which_row[col]]=atof(name);
			}		
		}
	}
	file_row=row;	//file row 
	fclose(fp);
//check feature_num
	if(feature_num<=1)
	{
		printf("Feature_Num wrong!!");
		return(0);
	}
//File attributes
	fp=fopen(argv[3],"w");
	fprintf(fp,"\nSUCESS\n"
						 "<feature file>:%s\n"
						 "<Matrix file>:%s\n"
						 "<Detailed results file>:%s\n\n"
						 "Version:07201030 <SPE && FMEAS> <100 find seed> <1000 arrangement>\n"
						 ,argv[1],argv[2],argv[3]);
	
	for(row=0;row<=feature_num;row++)
	{
		stp[row]=(max[row]-min[row])/copies;
		
		if(stp[row]==0)
		{
			feature_file[row].rule=5;
		}
		
		switch(feature_file[row].rule)
		{
			case 0:strcpy(name,"ignored");break;
			case 1:strcpy(name,"<");break;
			case 2:strcpy(name,">");break;
			case 3:strcpy(name,"<=");break;
			case 4:strcpy(name,">=");break;
			case 5:strcpy(name,"==");break;
			case 6:strcpy(name,"!=");break;
			default:strcpy(name,"ERROR");break;
		}
		strcpy(feature_file[row].symbol,name);
		have_this=0;
		for(col=1;col<=file_col;col++)
		{
			if(strcmp(feature_file[row].name,matrix_file[col].name)==0)
			{
				have_this=1;
				break;
			}
		}
		if(!have_this)
		{
			printf("Not Found %s\n",feature_file[row].name);
			fprintf(fp,"Not Found %s\n",feature_file[row].name);
		}
		else
		{
//			printf("Rule %s:%s\tmin=%f\tmax=%f\tstp=%f\n",feature_file[row].name,name,min[row],max[row],stp[row]);
			fprintf(fp,"Rule %s:%s\tmin=%f\tmax=%f\tstp=%f\n",feature_file[row].name,name,min[row],max[row],stp[row]);
		}
	}
	printf("\nMatrix_File:col=%d\trow=%d\nFeature_file:feature_num=%d\n\n",file_col,file_row,feature_num);
	fprintf(fp,"\nMatrix_File:col=%d\trow=%d\nFeature_file:feature_num=%d\n\n",file_col,file_row,feature_num);
	
//find seed
	best_TP=0; best_FP=0; best_TN=0; best_FN=0;
	best_SEN=0; best_PREC=0; best_FMEAS=0; best_SPE=0;
	for(seed_one=1;seed_one<=feature_num-1;seed_one++)
	{
		TP[0]=0; FP[0]=0; TN[0]=0; FN[0]=0;	
		SEN[0]=0; PREC[0]=0; SPE[0]=0; FMEAS[0]=0;
		better_one=0; better_another=0;
		better_feature_one=0; better_feature_another=0;
		
		for(incremental_one=1;incremental_one<=copies/speed;incremental_one++)
		{
			for(incremental_another=1;incremental_another<=copies/speed;incremental_another++)
			{
				for(seed_another=seed_one+1;seed_another<=feature_num;seed_another++)
				{
					TP[seed_another]=0; FP[seed_another]=0; TN[seed_another]=0; FN[seed_another]=0;
					SEN[seed_another]=0; PREC[seed_another]=0; SPE[seed_another]=0; FMEAS[seed_another]=0;
				}	
				for(row=1;row<=file_row;row++)
				{
					for(seed_another=seed_one+1;seed_another<=feature_num;seed_another++)
					{
						if((compare(1,min[seed_one]+stp[seed_one]*incremental_one*speed,file_mat[row][seed_one],feature_file[seed_one].rule)) 
							&& compare(1,min[seed_another]+stp[seed_another]*incremental_another*speed,file_mat[row][seed_another],feature_file[seed_another].rule))
						{
							if(file_mat[row][0]==1) TP[seed_another]++; else FP[seed_another]++;
						}
						else
						{
							if(file_mat[row][0]==1) FN[seed_another]++; else TN[seed_another]++;
						}
					}
				}
				for(seed_another=seed_one+1;seed_another<=feature_num;seed_another++)
				{
					SEN[seed_another]=(float)TP[seed_another]/(float)(TP[seed_another]+FN[seed_another]);
					PREC[seed_another]=(float)TP[seed_another]/(float)(TP[seed_another]+FP[seed_another]);
					SPE[seed_another]=(float)TN[seed_another]/(float)(TN[seed_another]+FP[seed_another]);
					FMEAS[seed_another]=2.0*SEN[seed_another]*PREC[seed_another]/(SEN[seed_another]+PREC[seed_another]);
					//--------------------------------find---seed-----inside----------------------------------------------------------------//
					if(FMEAS[seed_another]>=FMEAS[0])
					{
						TP[0]=TP[seed_another]; FP[0]=FP[seed_another]; TN[0]=TN[seed_another]; FN[0]=FN[seed_another];	
						SEN[0]=SEN[seed_another]; PREC[0]=PREC[seed_another]; SPE[0]=SPE[seed_another]; FMEAS[0]=FMEAS[seed_another];
						better_one=seed_one; better_another=seed_another;
						better_feature_one=min[seed_one]+stp[seed_one]*incremental_one*speed;
						better_feature_another=min[seed_another]+stp[seed_another]*incremental_another*speed;
					}
					//------------------------------------------------------------------------------------------------------------------------//
				}
			}
		}
		//---------------------------------------find------seed-------outside------------------------------------------------------------//
		if(FMEAS[0]>=best_FMEAS)
		{
			best_TP=TP[0]; best_FP=FP[0]; best_TN=TN[0]; best_FN=FN[0];	
			best_SEN=SEN[0]; best_PREC=PREC[0]; best_SPE=SPE[0]; best_FMEAS=FMEAS[0];
			best_one=better_one; best_another=better_another;
			feature_one=better_feature_one;
			feature_another=better_feature_another;
		}
		//------------------------------------------------------------------------------------------------------------------------//
		printf("NO.%d:%s%s%f\tNO.%d:%s%s%f\tBetter:\tTP=%d\tFP=%d\tTN=%d\tFN=%d\tSEN=%f\tPREC=%f\tSPE=%f\tFMEAS=%f\n",
		better_one,feature_file[better_one].name,feature_file[better_one].symbol,better_feature_one,
		better_another,feature_file[better_another].name,feature_file[better_another].symbol,better_feature_another,
		TP[0],FP[0],TN[0],FN[0],SEN[0],PREC[0],SPE[0],FMEAS[0]);

		fprintf(fp,"NO.%d:%s%s%f\tNO.%d:%s%s%f\tBetter:\tTP=%d\tFP=%d\tTN=%d\tFN=%d\tSEN=%f\tPREC=%f\tSPE=%f\tFMEAS=%f\n",
		better_one,feature_file[better_one].name,feature_file[better_one].symbol,better_feature_one,
		better_another,feature_file[better_another].name,feature_file[better_another].symbol,better_feature_another,
		TP[0],FP[0],TN[0],FN[0],SEN[0],PREC[0],SPE[0],FMEAS[0]);
	}
	//find seed 1000
	
	//for(feature_detail[best_one]=min[best_one];feature_detail[best_one]<=max[best_one];feature_detail[best_one]+=stp[best_one])
	//{
		//for(feature_detail[best_another]=min[best_another];feature_detail[best_another]<=max[best_another];feature_detail[best_another]+=stp[best_another])
		
	for(incremental_one=1; incremental_one<=copies; incremental_one++)
	{
		for(incremental_another=1; incremental_another<=copies; incremental_another++)
		{
			feature_detail[best_one]=min[best_one]+incremental_one*stp[best_one]; 
			feature_detail[best_another]=min[best_another]+incremental_another*stp[best_another];
			
			TP[0]=0;
			FP[0]=0;
			FN[0]=0;
			TN[0]=0;
			
			for(row=1;row<=file_row;row++)	
			{
				if(compare(1,feature_detail[best_one],file_mat[row][best_one],feature_file[best_one].rule) &&
					 compare(1,feature_detail[best_another],file_mat[row][best_another],feature_file[best_another].rule))
				{
					if(file_mat[row][0]==1) TP[0]++; else FP[0]++;
				}
				else
				{
					if(file_mat[row][0]==1) FN[0]++; else TN[0]++;
				}
			}
			SEN[0]=(float)TP[0]/(float)(TP[0]+FN[0]);
			PREC[0]=(float)TP[0]/(float)(TP[0]+FP[0]);
			SPE[0]=(float)TN[0]/(float)(TN[0]+FP[0]);
			FMEAS[0]=2.0*SEN[0]*PREC[0]/(SEN[0]+PREC[0]);
			//---------------------------------------seed------value------------------------------------------------------------------//	
			if(FMEAS[0]>=FMEAS_reg[0])
			{
				TP_reg[0]=TP[0]; FP_reg[0]=FP[0]; TN_reg[0]=TN[0]; FN_reg[0]=FN[0];
				SEN_reg[0]=SEN[0]; PREC_reg[0]=PREC[0]; FMEAS_reg[0]=FMEAS[0]; SPE_reg[0]=SPE[0];
				feature_one=feature_detail[best_one];
				feature_another=feature_detail[best_another];
			}
			//------------------------------------------------------------------------------------------------------------------------//
		}
	}
	feature_detail[best_one]=feature_one; feature_detail[best_another]=feature_another;
	seed[best_one]=1; seed[best_another]=2;
//output seed	
	fprintf(fp,"\nSeed:\tNO.%d:%s%s%f\tNO.%d:%s%s%f\tTP=%d\tFP=%d\tTN=%d\tFN=%d\tSEN=%f\tPREC=%f\tSPE=%f\tFMEAS=%f\n\n",
	best_one,feature_file[best_one].name,feature_file[best_one].symbol,feature_detail[best_one],
	best_another,feature_file[best_another].name,feature_file[best_another].symbol,feature_detail[best_another],
	best_TP,best_FP,best_TN,best_FN,best_SEN,best_PREC,best_SPE,best_FMEAS);
	
	printf("\n\nSeed:\tNO.%d:%s%s%f\tNO.%d:%s%s%f\tTP=%d\tFP=%d\tTN=%d\tFN=%d\tSEN=%f\tPREC=%f\tSPE=%f\tFMEAS=%f\n\n",
	best_one,feature_file[best_one].name,feature_file[best_one].symbol,feature_detail[best_one],
	best_another,feature_file[best_another].name,feature_file[best_another].symbol,feature_detail[best_another],
	best_TP,best_FP,best_TN,best_FN,best_SEN,best_PREC,best_SPE,best_FMEAS);
	
//main
	for(feauture_unit=3;feauture_unit<=feature_num;feauture_unit++)
	{
		//rst
		for(col=1;col<=feature_num;col++)
		{
			TP_reg[col]=0; FP_reg[col]=0; TN_reg[col]=0; FN_reg[col]=0;	
			SEN_reg[col]=0;PREC_reg[col]=0;SPE_reg[col]=0;FMEAS_reg[col]=0;
		}
		for(incremental_one=1;incremental_one<=copies;incremental_one++)
		{
			for(col=1;col<=feature_num;col++)
			{
				TP[col]=0; FP[col]=0; TN[col]=0; FN[col]=0; 
			}
			for(row=1;row<=file_row;row++)
			{
				en_seed=1;
				for(col=1;col<=feature_num;col++)
				{
					if(seed[col]!=0)
					{
						if(compare(1,feature_detail[col],file_mat[row][col],feature_file[col].rule)==0)
						{
							en[col]=1;
							en_seed=0;
							break;
						}
					}
					else
					{
						if(compare(1,min[col]+stp[col]*incremental_one,file_mat[row][col],feature_file[col].rule)==0)
							en[col]=0;
						else
							en[col]=1;
					}	
				}
				for(col=1;col<=feature_num;col++)
				{
					if(seed[col]==0)
					{
						if(en_seed && en[col])
						{
							if(file_mat[row][0]==1) TP[col]++; else FP[col]++;
						}
						else
						{
							if(file_mat[row][0]==1) FN[col]++; else TN[col]++;
						}
					}
				}
			}
			for(col=1;col<=feature_num;col++)
			{
				if(seed[col]==0)
				{
					SEN[col]=(float)TP[col]/(float)(TP[col]+FN[col]);
					PREC[col]=(float)TP[col]/(float)(TP[col]+FP[col]);
					SPE[col]=(float)TN[col]/(float)(TN[col]+FP[col]);
					FMEAS[col]=2.0*SEN[col]*PREC[col]/(SEN[col]+PREC[col]);
					//-----------------------------------------compare----seed----inside------------------------------------------------------//
					if(FMEAS[col]>=FMEAS_reg[col])
					{
						TP_reg[col]=TP[col]; FP_reg[col]=FP[col]; TN_reg[col]=TN[col]; FN_reg[col]=FN[col];	
						SEN_reg[col]=SEN[col]; PREC_reg[col]=PREC[col]; SPE_reg[col]=SPE[col]; FMEAS_reg[col]=FMEAS[col];
						feature_detail_reg[col]=min[col]+stp[col]*incremental_one;
					}
					//------------------------------------------------------------------------------------------------------------------------//
				}
			}
			
		}
		new_seed=0;
		for(col=1;col<=feature_num;col++)
		{
			if(seed[col]==0)
			{
//				printf("NO.%d:%s%s%f\tTP=%d\tFP=%d\tTN=%d\tFN=%d\tSEN=%f\tPREC=%f\tSPE=%f\tFMEAS=%f\n",
//				col,feature_file[col].name,feature_file[col].symbol,feature_detail_reg[col],
//				TP_reg[col],FP_reg[col],TN_reg[col],FN_reg[col],
//				SEN_reg[col],PREC_reg[col],SPE_reg[col],FMEAS_reg[col]);
				
				fprintf(fp,"NO.%d:%s%s%f\tTP=%d\tFP=%d\tTN=%d\tFN=%d\tSEN=%f\tPREC=%f\tSPE=%f\tFMEAS=%f\n",
				col,feature_file[col].name,feature_file[col].symbol,feature_detail_reg[col],
				TP_reg[col],FP_reg[col],TN_reg[col],FN_reg[col],SEN_reg[col],PREC_reg[col],SPE_reg[col],FMEAS_reg[col]);
				//------------------------------------------add----seed-----outside----------------------------------------------------------------//
				if((SPE_reg[col]-best_SPE>=SPE_incremental && best_FMEAS-FMEAS_reg[col]<=FMEAS_reduction) ||
					 (FMEAS_reg[col]-best_FMEAS>=FMEAS_incremental && best_SPE-SPE_reg[col]<=SPE_reduction) ||
					 (FMEAS_reg[col]>best_FMEAS && SPE_reg[col]>best_SPE) )
				{
					best_TP=TP_reg[col]; best_FP=FP_reg[col]; best_TN=TN_reg[col]; best_FN=FN_reg[col];
					best_SEN=SEN_reg[col]; best_PREC=FP_reg[col]; best_FMEAS=FMEAS_reg[col]; best_SPE=SPE_reg[col];
					new_seed=col; best_feature_detail=feature_detail_reg[col];
				}
				//------------------------------------------------------------------------------------------------------------------------//
			}
		}
		
		if(new_seed==0)
		{
//			printf("\nNO better!!OVER\n\n");	
			fprintf(fp,"\nNO better!!OVER\n\n");
			break;
		}
		else
		{
//			printf("\nBetter:\tNO.%d:%s%s%f\tFMEAS=%f\n\n",
//			new_seed,feature_file[new_seed].name,feature_file[new_seed].symbol,feature_detail_reg[new_seed],best_FMEAS);
			
			fprintf(fp,"\nBetter:\tNO.%d:%s%s%f\tFMEAS=%f\n\n",
			new_seed,feature_file[new_seed].name,feature_file[new_seed].symbol,feature_detail_reg[new_seed],best_FMEAS);
		
			seed[new_seed]=feauture_unit;
			feature_detail[new_seed]=best_feature_detail;
		}
			
	}
//output
	for(m_num=1;m_num<=feauture_unit;m_num++)
	{
		for(feature_which=1;feature_which<=feature_num;feature_which++)
		{
			if(seed[feature_which]==m_num)
			{
				fprintf(fp,"NO.%d\tfeature[%d]:%s%s%f\t\n",
				seed[feature_which],feature_which,feature_file[feature_which].name,feature_file[feature_which].symbol,feature_detail[feature_which]);
  	  	
				printf("NO.%d\tfeature[%d]:%s%s%f\t\n",
				seed[feature_which],feature_which,feature_file[feature_which].name,feature_file[feature_which].symbol,feature_detail[feature_which]);
				
				break;
			}
		}
	}
	for(feature_which=1;feature_which<=feature_num;feature_which++)
	{
		if(seed[feature_which]==0)
		{
			fprintf(fp,"NO.%d\tfeature[%d]:%s%s%f\t\n",
			seed[feature_which],feature_which,feature_file[feature_which].name,feature_file[feature_which].symbol,feature_detail[feature_which]);
    	
//			printf("NO.%d\tfeature[%d]:%s%s%f\t\n",
//			seed[feature_which],feature_which,feature_file[feature_which].name,feature_file[feature_which].symbol,feature_detail[feature_which]);
		}
	}
	printf("\nbest_TP=%d\tbest_FP=%d\tbest_TN=%d\tbest_FN=%d\n"
					 "best_SEN=%f\tbest_SPE=%f\tbest_FMEAS=%f\tbest_ACC=%f\n\n",
					 best_TP,best_FP,best_TN,best_FN,best_SEN,best_SPE,best_FMEAS,(float)(best_TP+best_TN)/(float)(best_TP+best_FP+best_TN+best_FN));

	fprintf(fp,"\nbest_TP=%d\tbest_FP=%d\tbest_TN=%d\tbest_FN=%d\n"
							 "best_SEN=%f\tbest_SPE=%f\tbest_FMEAS=%f\tbest_ACC=%f\n\n",
								best_TP,best_FP,best_TN,best_FN,best_SEN,best_SPE,best_FMEAS,(float)(best_TP+best_TN)/(float)(best_TP+best_FP+best_TN+best_FN));

	for(m_num=1;m_num<=feauture_unit;m_num++)
	{
		for(feature_which=1;feature_which<=feature_num;feature_which++)
		{
			if(seed[feature_which]==m_num)
			{
				fprintf(fp,"$%d%s%f && ",
				which_col[feature_which],feature_file[feature_which].symbol,feature_detail[feature_which]);
				
				printf("$%d%s%f && ",
				which_col[feature_which],feature_file[feature_which].symbol,feature_detail[feature_which]);
				
				break;
			}
		}
	}
	printf("\n\n");
	
	for(ti = 0   ;  ti <  total_row ;  ti++)
		free(file_mat[ti]);
	free(file_mat);
	
	fclose(fp);
	
}

int compare(int en,float feature_detail,float matrix_value,int rule)
{
	int result;
	if(en==-1)
		result=1;
	else
	switch(rule)
	{
		case 0:result=1;break;
		case 1:if(matrix_value<feature_detail)result=1;else result=0;break;
		case 2:if(matrix_value>feature_detail)result=1;else result=0;break;
		case 3:if(matrix_value<=feature_detail)result=1;else result=0;break;
		case 4:if(matrix_value>=feature_detail)result=1;else result=0;break;
		case 5:if(matrix_value==feature_detail)result=1;else result=0;break;
		case 6:if(matrix_value!=feature_detail)result=1;else result=0;break;
		default:result=0;break;
	}
	return(result);
}
