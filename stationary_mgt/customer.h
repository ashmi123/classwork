#include <stdio.h>
typedef struct customer
{
   int id;
   char name[32];
   char addr[32];
   char mobile[32];
   char email[32];

}cust;

void manage_customer(cust *c);
void accept_customer(cust *c);
void display_customer();
cust* find_customer(cust c);
int menu_customer();
void edit_customer(cust c);
void delete_customer(cust c);
void write_in_file(cust c);