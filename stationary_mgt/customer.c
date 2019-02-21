#include<stdio.h>
#include<stdlib.h>
#include "customer.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int menu_customer()
{
   int choice;
   printf("Enter your choice as follows\n");
   printf("0.Exit\n");
   printf("1.Accept Customer\n");
   printf("2.Display Customer\n");
   printf("3.Find Customer\n");
   printf("4.Edit Customer\n") ;
   printf("5.Delete Cusstomer\n");
   scanf("%d",&choice);
   return choice;
}

void manage_customer(cust *c)
{
   int choice;
   cust c1;
   while(1)
   {
       switch(choice=menu_customer())
       {
       case 0:
           return  ;
       case 1:
           accept_customer(c);
           break;
       case 2:
           display_customer();
           break  ;
       case 3:
           printf("Enter the name of customer you want find ....");
           scanf("%s",c1.name);
           find_customer(c1);
           break;
       case 4:
            printf("Enter the name of customer you want find ....");
            scanf("%s",c1.name);
            edit_customer(c1);
            break;  
       case 5:
       printf("Enter the name of customer you want find ....");
       scanf("%s",c1.name);
       delete_customer(c1); 
       break;    
       default:
       printf("Enter Valid Choice !!!!\n");        
       }
   }

}
void accept_customer(cust *c)
{
  int fd;
  fd=open("customer.db",O_CREAT|O_WRONLY|O_APPEND,0644);

  if(fd<0)
  {
      printf("open() failed :( \n");
      _exit(1);
  }
  printf("Enter Id : ");
  scanf("%d",&c->id);
  printf("Enter Name : ");
  scanf("%s",c->name);
  printf("Enter Address : ");
  scanf("%s",c->addr);
  printf("Enter Mobile Number : ");
  scanf("%s",c->mobile);
  printf("Enter EmailId : ");
  scanf("%s",c->email);

  write(fd,c,sizeof(cust));
  close(fd);
}

void display_customer()
{
    int fd;
    cust c; 
    fd = open("customer.db",O_RDONLY);
    if(fd<0)
    {
        printf("open() failed :( \n");
        _exit(1);
    }
    printf("\t\t**********List of Customers*********\n");
    while( read(fd,&c,sizeof(cust)) > 0 )
    {

    printf("\nId :            %d\n",c.id);
    printf("Name :          %s\n",c.name);
    printf("Address :       %s\n",c.addr);
    printf("Mobile number : %s\n",c.mobile);
    printf("emailid  :      %s\n",c.email);
    }
    close(fd);
}
cust* find_customer(cust c1)
{
    int fd,flag=0;
    cust c2;
    cust *c3;
    fd = open("customer.db",O_RDONLY);
    if(fd<0)
    {
        printf("open() failed :( \n");
        _exit(1);
    }
    while( read(fd,&c2,sizeof(cust)) > 0 )
    {
      if( strcmp(c1.name,c2.name) == 0)
      {
          flag=1;
          break;
      }      
    }
    if(flag==1)
    {
        printf("Customer Found :)  \n");
        printf("c1::%s\n",c1.name);
        c3=&c2;
    return c3;
    }
    else
    {
        printf("Customer NOT found\n");
        return NULL;
    }
    close(fd);

}
void edit_customer(cust c1)
{
   int fd;
   cust c2;
   fd = open("customer.db",O_RDWR);
   if(fd < 0)
   {
       printf("open failed\n");
       _exit(0);
   }
   while(read(fd ,&c2,sizeof(cust) ) >0)
   {
    if( strcmp(c1.name,c2.name) == 0)
    {
        printf("customer found\n");
        printf("enter new details\n");
        printf("Enter new name : ");
        scanf("%s",c2.name);
        lseek(fd,-sizeof(cust),SEEK_CUR);
        write(fd,&c2,sizeof(cust));
    }
   }

}
void delete_customer(cust c1)
{
   int fd,fc;
   cust temp;
   fd=open("customer.db",O_RDONLY);
   if(fd < 0)
   {
       printf("open failed\n");
       _exit(0);
   }

   fc=open("temp.db",O_CREAT|O_WRONLY,0644);
   if(fd < 0)
   {
       printf("open failed\n");
       _exit(0);
   }
   while(read(fd,&temp,sizeof(cust)) >0)
   {
       if(strcmp(c1.name,temp.name)!=0)
       {
           printf("in if....strcmp\n");
           write(fc,&temp,sizeof(cust));
       }
   }
   printf("outside while\n");

   open("temp.db",O_RDONLY,0644);
   while(read(fc,&temp,sizeof(cust)) >0)
   {
      printf("temp name : %s",temp.name);
   }
   close(fd);
   close(fc);
  unlink("customer.db");
  rename("temp.db","customer.db");
} 

