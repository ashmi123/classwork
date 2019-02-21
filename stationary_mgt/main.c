#include<stdio.h>
#include<stdlib.h>
#include "customer.h"
#include "item.h"


int menuChoice();
int main()
{
	   
		int choice;
		cust c1;
		item i1;
        printf("\t\t\t\t Stationary Management \n");
           			
		while(1)
		{
			switch(choice=menuChoice())
			{
			  case 0:
			  exit(0);
			  case 1:
			  printf("********CUSTOMER MANAGEMENT*******\n");
              manage_customer(&c1);
			  break;
			  case 2:
			  printf("********ITEM MANAGEMENT*******\n");
			  manage_item(&i1);
			  break;
			  case 3:
			  printf("********SALES MANAGEMENT*****\n");
			  break;
			  default:
			  printf("Please Enter valid choice \n");
			  break;
	        }
		}
		return 0;
}
int menuChoice()
{
	int choice;
	printf("Enter your choice as follows : \n");
	printf("0.Exit\n");
	printf("1.Customer Management\n");
	printf("2.Item Management\n");
	printf("3.Sales Management\n");
	scanf("%d",&choice);
	return choice;

}