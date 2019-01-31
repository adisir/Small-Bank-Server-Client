#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sl.h"

SortedListPtr SLCreate(CompareFuncT cf, DestructFuncT df){
	SortedListPtr list = (SortedListPtr)malloc(sizeof(struct SortedList));
	list->compare = cf;
	list->exclude = df;
	list->head= NULL;		
	return list;
}

void SLDestroy(SortedListPtr list){
	//this will start the process of deleting the main SLcreate list and pointers associated ot it
	
	Node *exterminator = list->head;
	while (exterminator != NULL){
		Node *exterminatorSub =exterminator;
		exterminator = exterminator->next;
		free(exterminatorSub); 
		if (exterminator->next ==NULL){
			free(exterminator);
			free(list);
			return;
		}
	}
	//accounts for the last node which will be taken care of here.
	
	free(list);
	return;
}
int SLInsert(SortedListPtr list, void *newObj){
	//these pointers will be used in the sorting insert as we go along
	Node *ptrPrev=NULL;
	Node *ptrCurr=list->head; 
	
	//first case when there is nothing in list, just put head and the newobj as head
	if (list->head == NULL){
	Node* temp = malloc(sizeof(Node));
	temp->data = newObj;
	temp->count = 1;
	list->head = temp;
	return 1;
	}
		//itterates through to find a place to plop the node
	while (ptrCurr != NULL && list->compare(ptrCurr->data, newObj )>0){
		ptrPrev = ptrCurr;
		ptrCurr = ptrCurr->next;

	}
		//if we need to add at the start of head when its greatest
	if (ptrPrev==NULL && list->compare(ptrCurr->data, newObj) <0){
		Node* temp = malloc(sizeof(Node));
		temp->data= newObj;
		temp->count = 1;
		list->head->count--;
		temp->next=list->head;
		list->head = temp;
		return 1;
		
	}
	if(ptrPrev==NULL && list->compare(ptrCurr->data, newObj)==0){ // same object
		return 0;
	}	

		//if we reach the end, just add to end
	if(ptrCurr == NULL){
		Node* temp = malloc(sizeof(Node));
		temp->count = 0;
		temp->data = newObj;
		ptrPrev->next = temp;
		return 1;

	}  if (list->compare(ptrCurr->data, newObj)==0) {
		return 0;
	// list has reached end, just put it at the end now since it is smallest item
	} else {
		Node* temp = malloc(sizeof(Node));
		temp->data = newObj;
		temp->count = 0;
		temp->next = ptrCurr;
		ptrPrev->next = temp;
		return 1;
	}

	return 0;

}

int SLRemove(SortedListPtr list, void *newObj){
	Node* curr = list->head;
	Node* prev = NULL;

	while(curr != NULL){
		if(curr->data == newObj){
			curr->count--;
			if(prev == NULL){ //if we are removing the head 
				list->head = curr->next;
				list->head->count++;
				if(curr->count < 1){
					free(curr);		
				}
				return 1;
			}
			Node* temp = curr;
			prev->next = curr->next;
			if(curr->count < 1){
				free(curr);
			}
			return 1;
		}else{
			prev = curr;
			curr = curr->next;
		}
	}

	return 0;
}

SortedListIteratorPtr SLCreateIterator(SortedListPtr list){

   SortedListIteratorPtr sli = (SortedListIteratorPtr) malloc(sizeof(struct SortedListIterator));
	//check to see if there is nothing in list and makes sure we don't create and empty list for no reason
      if(sli == NULL || list == NULL){
          // This is so that if the list does not contain any value inside for anything to read
          return NULL;

      }else{
          // This turns the pointer to move it forwards along with the list and then return
          sli->current = list->head;
                   
         return sli;


}
}

void SLDestroyIterator(SortedListIteratorPtr iter){
	if(iter->current == NULL){
		free(iter);
	}else{
		iter->current->count--;
		free(iter);
	}
}

void * SLNextItem(SortedListIteratorPtr iter){
	if(iter->current==NULL){

        	 // The item in the next section does not contain any data
         	 return NULL;
      	}
      	//decrement pointer counter by one
	iter->current->count--;
         // Continue down to the next node next
        iter->current = iter->current->next;
      return SLGetItem(iter);

}

void * SLGetItem( SortedListIteratorPtr iter ){
	//if nothing inside return
	if(iter->current==NULL){
		return NULL;
	}
	else{
		//increment pointer by 1
		iter->current->count++;
		//Just get data from current node which was set up by SLNextItem
		return iter->current->data;
	}

}




