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
	if(c==1)
	{
		switch( chr[0] )
		{
//			case 'M' :  num=23; break;
			case 'X' :  num=24; break;
			case 'Y' :  num=25; break;
			default  :  num=chr[0]-48; break;
		}		
	}
	else if(c==2)
	{
		switch( chr[0] )
		{
			case 'M' :  num=23; break;
			default  :  num = (chr[0]-48)*10 + chr[1]-48;
		}
	}
	else num =0;
	return num;
}
