//
// Created by dvir on 12/22/22.
//
#include "HashTable.h"
#include "MultiValueHashTable.h"
#include "LinkedList.h"

//functions to send to the hash.
Element copyList(Element element){
    return element;
}
status freeList(Element element){
    LinkedList linkedList = (LinkedList)element;
    return destroyList(linkedList);
}
status printList(Element element){
    LinkedList linkedList = (LinkedList)element;
    return displayList(linkedList);
}
//use hash so every value in the pair is linked list
struct MultiValueHashTable_t {
    hashTable hash;
    int hashSize;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction valueCompare;
    EqualFunction equalPart;
    PrintFunction printKey;
};

MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber, EqualFunction equalValue, EqualFunction equalPart){
    if(copyKey == NULL||freeKey==NULL||printKey==NULL||copyValue==NULL||freeValue==NULL|| printValue==NULL|| equalKey==NULL||transformIntoNumber==NULL|| hashNumber<= 0||equalValue==NULL){
        return NULL;
    }
    MultiValueHashTable multiHash = (MultiValueHashTable) malloc(sizeof (struct MultiValueHashTable_t));
    if(multiHash == NULL){
        return NULL;
    }
    //the key is element and the value is list of elements
    multiHash->hash = createHashTable(copyKey, freeKey, printKey, copyList, freeList, printList, equalKey, transformIntoNumber, hashNumber);
    if(multiHash->hash == NULL){
        return NULL;
    }
    multiHash->hashSize = hashNumber;
    multiHash->copyValue = copyValue;
    multiHash->freeValue = freeValue;
    multiHash->printValue = printValue;
    multiHash->equalPart = equalPart;
    multiHash->valueCompare = equalValue;
    multiHash->printKey = printKey;
    return multiHash;

}


status destroyMultiValueHashTable(MultiValueHashTable multiValueHashTable){
    if(multiValueHashTable == NULL){
        return failure;
    }
    destroyHashTable(multiValueHashTable->hash);
    free(multiValueHashTable);
    return success;
}

status addToMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element value){
    if(multiValueHashTable == NULL|| key == NULL|| value == NULL){
        return failure;
    }
    LinkedList linkedList = lookupInHashTable(multiValueHashTable->hash,key);
    //first value mapped to this key
    if(linkedList == NULL){
        linkedList = createLinkedList(multiValueHashTable->copyValue, multiValueHashTable->freeValue, multiValueHashTable->printValue, multiValueHashTable->valueCompare, multiValueHashTable->equalPart);
        if(linkedList == NULL){
        	return MemoryProblem;
        }
        if(appendNode(linkedList,value)==MemoryProblem){
        	return MemoryProblem;
        }
        if(addToHashTable(multiValueHashTable->hash,key, linkedList)== MemoryProblem){
        	return MemoryProblem;
        }
        return success;
    }
    //add value to the value list
    if(appendNode(linkedList,value)==MemoryProblem){
            	return MemoryProblem;
            }
    return success;
}

Element lookupInMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key){
    return lookupInHashTable(multiValueHashTable->hash,key);
}

status removeFromMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element valuePart){
    if(multiValueHashTable == NULL|| key == NULL|| valuePart == NULL){
        return failure;
    }
    LinkedList linkedList = lookupInHashTable(multiValueHashTable->hash,key);
    if(linkedList == NULL){
        return failure;
    }
    Element del_val = searchByKeyList(linkedList,valuePart);
    if(del_val == NULL){
        return failure;
    }
    deleteNode(linkedList,del_val);
    if(getLengthList(linkedList) == 0){
        removeFromHashTable(multiValueHashTable->hash,key);
        return success;
    }
    return success;
}

status displayMultiValueHashElementsByKey(MultiValueHashTable multiValueHashTable, Element key){
    if(multiValueHashTable == NULL || key == NULL){
        return failure;
    }
    LinkedList linkedList = lookupInHashTable(multiValueHashTable->hash,key);
    if(linkedList == NULL){
        return failure;
    }
    multiValueHashTable->printKey(key);
    displayList(linkedList);
    return success;
}
