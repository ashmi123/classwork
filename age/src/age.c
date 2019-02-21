/*
 ============================================================================
5 Name        : age.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
int main()
{
	int a,b,c,max;
	printf("enter three numbers ..");
	scanf("%d%d%d",&a,&b,&c);
	if(a>b)
	{if(a>c)
		max=a;
	else max=c;
	}
	else{
		if(b>c)max=b;
		else max=c;
	}
	printf("maximum =%d",max);

}


