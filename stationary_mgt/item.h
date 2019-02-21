#include <stdio.h>
typedef struct item
{
   int id;
   char name[32];
   int quantity;
   float price;

}item;

void manage_item(item *i);
void accept_item(item *i);
void display_item();
item* find_item(item i);
int menu_item();
void edit_item(item i);
void delete_item(item i);
void quantity_adjust(item i);
//void write_in_file(item i);