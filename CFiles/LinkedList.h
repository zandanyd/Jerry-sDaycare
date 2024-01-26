//
// Created by dvir on 12/18/22.
//

#ifndef UNTITLED2_LINKEDLIST_H
#define UNTITLED2_LINKEDLIST_H
#include "Defs.h"

typedef struct  LinkedList_t* LinkedList;


//create new linked list need: copy, free, print and equal functions for the element that use this LinkedList.
LinkedList createLinkedList(CopyFunction copyFunction, FreeFunction freeFunction, PrintFunction printFunction,
                            EqualFunction equalFunction, EqualFunction haveKeyFunction );

// clean and free the memory of the linked list use the free function to destroy the elements as well.
//destroy the element copy.
status destroyList(LinkedList linkedList);
// add element to the end of the list
//return failure if get bad arguments or have memory problem.
status appendNode(LinkedList linkedList, Element element);
// find the element and delete it.
//return failure if get bad arguments or have memory problem.
status deleteNode(LinkedList linkedList, Element element);
// print all the linked list elements from the first to the last in the order they get in.
//return failure if get bad arguments or have memory problem.
status displayList(LinkedList linkedList);
// find and return the value of the element in the index place in the linked list the index start with 1.
//return Null if get bad arguments.
Element getDataByIndex(LinkedList linkedList, int index);
// return number of elements in the list.
//return Null if get bad arguments.

int getLengthList(LinkedList linkedList);
// find and return node with the key.
//return Null if get bad arguments or does'nt found.
Element searchByKeyList(LinkedList linkedList, Element key);







#endif //UNTITLED2_LINKEDLIST_H
