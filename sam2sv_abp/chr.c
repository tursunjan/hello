#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
//#include "sam2sv.h"

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
