#ifndef SL_H
#define SL_H

#include <stdlib.h>

typedef int (*CompareFuncT)( void *, void * );
typedef void (*DestructFuncT)( void * );

typedef struct node_{
void* data;
void* next;
int count;

}Node;

struct SortedList
{
CompareFuncT compare;
DestructFuncT exclude;
int items;
Node* head;
};
typedef struct SortedList* SortedListPtr;

 //SLCreate creates a new, empty, 'SortedList'.

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df);

 //SLDestroy destroys a SortedList 

void SLDestroy(SortedListPtr list);

 //SLInsert inserts a given data item 'newObj' into a SortedList 
 
int SLInsert(SortedListPtr list, void *newObj);

//SLRemove should remove 'newObj' from the SortedList 

int SLRemove(SortedListPtr list, void *newObj);

 //A SortedListIterator provides a one-way traversal through all of a SortedList
 
struct SortedListIterator
{
   Node* current;  
  DestructFuncT destruct;    
 };
typedef struct SortedListIterator* SortedListIteratorPtr;
SortedListIteratorPtr SLCreateIterator(SortedListPtr list);
void SLDestroyIterator(SortedListIteratorPtr iter);
void * SLNextItem(SortedListIteratorPtr iter);
void * SLGetItem( SortedListIteratorPtr iter );

#endif
