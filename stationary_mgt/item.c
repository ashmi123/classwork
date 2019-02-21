#include<stdio.h>
#include<stdlib.h>
#include "item.h"
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int menu_item()
{
   int choice;
   printf("Enter your choice as follows\n");
   printf("0.Exit\n");
   printf("1.Accept Item\n");
   printf("2.Display Item\n");
   printf("3.Find Item\n");
   printf("4.Edit Item\n") ;
   printf("5.Delete Item\n");
   printf("6.Modify Quantity\n");
   scanf("%d",&choice);
   return choice;
}

void manage_item(item *i)
{
   int choice;
   item i1;
   while(1)
   {
       switch(choice=menu_item())
       {
       case 0:
           return  ;
       case 1:
           accept_item(i);
           break;
       case 2:
           display_item();
           break  ;
       case 3:
           printf("Enter the name of item you want find ....");
           scanf("%s",i1.name);
           find_item(i1);
           break;
       case 4:
            printf("Enter the name of item you want edit ....");
            scanf("%s",i1.name);
            edit_item(i1);
            break;  
       case 5:
       printf("Enter the name of item you want find ....");
       scanf("%s",i1.name);
       delete_item(i1); 
       break; 
       case 6:
       printf("Enter the name of item to modify quantity ....");
       scanf("%s",i1.name);
       quantity_adjust(i1);   
       break;
       default:
       printf("Enter Valid Choice !!!!\n");        
       }
   }

}
void accept_item(item *i)
{
  int fd;
  fd=open("item.db",O_CREAT|O_WRONLY|O_APPEND,0644);

  if(fd<0)
  {
      printf("open() failed :( \n");
      _exit(1);
  }
  printf("Enter Id : ");
  scanf("%d",&i->id);
  printf("Enter Name : ");
  scanf("%s",i->name);
  printf("Enter Price : ");
  scanf("%f",&i->price);
  printf("Enter Quantity : ");
  scanf("%d",&i->quantity);

  write(fd,i,sizeof(item));
  close(fd);
}

void display_item()
{
    int fd;
    item i; 
    fd = open("item.db",O_RDONLY);
    if(fd<0)
    {
        printf("open() failed :( \n");
        _exit(1);
    }
    printf("\t\t**********List of Items*********\n");
    while( read(fd,&i,sizeof(item)) > 0 )
    {

    printf("\nId :            %d\n",i.id);
    printf("Name :          %s\n",i.name);
    printf("Price :       %f\n",i.price);
    printf("Quantity : %d\n",i.quantity);

    }
    close(fd);
}
item* find_item(item i1)
{
    int fd,flag=0;
    item i2;
    item *i3;
    fd = open("item.db",O_RDONLY);
    if(fd<0)
    {
        printf("open() failed :( \n");
        _exit(1);
    }
    while( read(fd,&i2,sizeof(item)) > 0 )
    {
      if( strcmp(i1.name,i2.name) == 0)
      {
          flag=1;
          break;
      }      
    }
    if(flag==1)
    {
        printf("Item Found :)  \n");
        printf("i1::%s\n",i1.name);
        i3=&i2;
    return i3;
    }
    else
    {
        printf("Item NOT found\n");
        return NULL;
    }
    close(fd);

}
void edit_item(item i1)
{
   int fd;
   item i2;
   fd = open("item.db",O_RDWR);
   if(fd < 0)
   {
       printf("open failed\n");
       _exit(0);
   }
   while(read(fd ,&i2,sizeof(item) ) >0)
   {
    if( strcmp(i1.name,i2.name) == 0)
    {
        printf("item found\n");
        printf("enter new details\n");
        printf("Enter new name : ");
        scanf("%s",i2.name);
        lseek(fd,-sizeof(item),SEEK_CUR);
        write(fd,&i2,sizeof(item));
    }
   }

}
void delete_item(item i1)
{
   int fd,fc;
   item temp;
   fd=open("item.db",O_RDONLY);
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
   while(read(fd,&temp,sizeof(item)) >0)
   {
       if(strcmp(i1.name,temp.name)!=0)
       {
     //      printf("in if....strcmp\n");
           write(fc,&temp,sizeof(item));
       }
   }
   //printf("outside while\n");

   open("temp.db",O_RDONLY,0644);
   while(read(fc,&temp,sizeof(item)) >0)
   {
      printf("temp name : %s",temp.name);
   }
   close(fd);
   close(fc);
  unlink("item.db");
  rename("temp.db","item.db");
} 
void quantity_adjust(item i1)
{
    int fd,quantity,choice;
    item i2;
    fd = open("item.db",O_RDWR);
    if(fd < 0)
    {
        printf("open failed\n");
        _exit(0);
    }
    while(read(fd ,&i2,sizeof(item) ) >0)
    {
     if( strcmp(i1.name,i2.name) == 0)
     {
         printf("item found\n");
         printf("Enter your choice as follows : \n ");
         printf("1.Add Quantity\n");
         printf("2.Subtract Quantiy\n");
         scanf("%d",&choice);
         switch(choice)
         {
             case 1:printf("enter quantity :");
                    scanf("%d",&quantity);
                    printf("old quan : %d\n",i2.quantity);
                    i2.quantity=i2.quantity+quantity;
                    printf("new quan : %d\n",i2.quantity);
                    lseek(fd,-sizeof(item),SEEK_CUR);
                    write(fd,&i2,sizeof(item));
                    printf("quantity modified\n");
                    
                    break;

             case 2:printf("enter quantity :");
             scanf("%d",&quantity);
             i2.quantity=i2.quantity-quantity;
             lseek(fd,-sizeof(item),SEEK_CUR);
             write(fd,&i2,sizeof(item));
             printf("quantity modified \n");
             break;       
         }


         
     }
    }
   
}
