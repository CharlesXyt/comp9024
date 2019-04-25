// Linked list interface ... COMP9024 17s2
#include <stdbool.h>
#include <string.h>

typedef struct Node *List;




List insertLL(List,char*);
List deleteLL(List, char*);
bool inLL(List, char*);
void freeLL(List);
void showLL(List);