
//
// Created by dvir on 12/18/22.
//
#include "LinkedList.h"
//struct node to use in LinkedList.
struct Node_t{
    Element data ;
    struct Node_t *next;

};

typedef struct Node_t *Node;

// contain pointer to the head and the end of the list, the size of the list, and the functions it needs.
struct LinkedList_t{
    Node head;
    Node tail;
    int size;
    CopyFunction copyElement;
    FreeFunction freeElement;
    PrintFunction printElement;
    EqualFunction compareElements;
    EqualFunction haveKey;

};


status destroyList(LinkedList linkedList){
    if (linkedList == NULL){
        return failure;
    }
    Node curr = linkedList->head;
    //for each node.
    while(curr!= NULL){
        Node temp = curr->next;
        linkedList->freeElement(curr->data);
        free(curr);
        curr = temp;
    }
    free(linkedList);
    return success;
}

LinkedList createLinkedList(CopyFunction copyFunction, FreeFunction freeFunction, PrintFunction printFunction,
                            EqualFunction equalFunction, EqualFunction haveKeyFunction ){
    LinkedList linkedList = (LinkedList) malloc(sizeof(struct LinkedList_t));
    if(linkedList == NULL){
    	//memory problem
        return NULL;
    }
    linkedList->size = 0;
    linkedList->freeElement = freeFunction;
    linkedList->compareElements = equalFunction;
    linkedList->haveKey = haveKeyFunction;
    linkedList->printElement =printFunction;
    linkedList->copyElement = copyFunction;
    return linkedList;
}

status appendNode(LinkedList linkedList, Element element){
    if (element==NULL || linkedList==NULL){
        return failure;
    }
    Element new_element = linkedList->copyElement(element);
    if(new_element ==NULL){
        return MemoryProblem;
    }
    //create node
    Node new_node = (Node)malloc(sizeof (struct Node_t));
    if(new_node ==NULL){
    	return MemoryProblem;
    }
    new_node->data = new_element;
    new_node->next = NULL;
    //if first node.
    if (linkedList->size == 0){

        linkedList->head = new_node;
        linkedList->tail = new_node;
    }
    else{
        linkedList->tail->next = new_node;
        linkedList->tail = new_node;
    }
    linkedList->size++;
    return success;
}

status deleteNode(LinkedList linkedList, Element element){
    if (element==NULL || linkedList==NULL){
        return failure;
    }
    Node curr = linkedList->head;
    //find the node we want to delete.
    //if the node is the head.
    if(linkedList->compareElements(element, curr->data) == true){
        Node temp = curr->next;
        //use the function we got from the user.
        linkedList->freeElement(curr->data);
        curr->next = NULL;
        free(curr);
        linkedList->head = temp;
        linkedList->size--;
        return success;
    }
    //find if the rest have this element.
    while(curr->next != NULL){
        if (linkedList->compareElements(element, curr->next->data) == true){
            Node temp = curr->next->next;
            linkedList->freeElement(curr->next->data);
            curr->next->next = NULL;
            free(curr->next);
            curr->next = temp;
            if(curr->next == NULL){
                linkedList->tail = curr;
            }

            linkedList->size--;
            return success;
        }
        curr = curr->next;
    }
    return failure;
}

status displayList(LinkedList linkedList){
    if(linkedList == NULL){
        return failure;
    }
    Node curr = linkedList->head;
    //for each node.
    while (curr != NULL){
    	//the function we got from the user.
        linkedList->printElement(curr->data);
        curr=curr->next;
    }
    return success;
}

Element getDataByIndex(LinkedList linkedList, int index){
    if(linkedList == NULL){
        return NULL;
    }
    if (index > linkedList->size){
        return NULL;
    }
    Node curr = linkedList->head;
    //go to the node in the index place.
    for (int i = 1; i< index; i++){
        curr = curr->next;
    }
    return curr->data;
}

int getLengthList(LinkedList linkedList){
    return linkedList->size;
}

Element searchByKeyList(LinkedList linkedList, Element key){
    if(linkedList == NULL || key == NULL){
        return NULL;
    }
    Node curr = linkedList->head;
    while (curr != NULL){
    	//function we got from the user.
        if(linkedList->haveKey(curr->data, key) == true){
            return curr->data;
        }
        curr=curr->next;
    }
    return NULL;
}
