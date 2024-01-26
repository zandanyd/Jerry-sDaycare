//
// Created by dvir on 12/19/22.
//
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"

//use array of linked lists, every key maped by the key element transform integer dived by the size of the array.
//every element of the linked list is keyValuePair.
struct hashTable_s{
    LinkedList *array;
    int hashSize;
    CopyFunction copyKey;
    FreeFunction freeKey;
    PrintFunction printKey;
    CopyFunction copyValue;
    FreeFunction freeValue;
    PrintFunction printValue;
    EqualFunction equalKey;
    TransformIntoNumberFunction transformIntoNumber;
};

//create the functions that we need to send to the linked list working on keyValue pairs.
Element copyPair(Element element){

    return element;
}

status freePair(Element element){
    KeyValuePair keyValuePair = (KeyValuePair)element;
    return destroyKeyValuePair(keyValuePair);
}

status printPair(Element element){
    KeyValuePair keyValuePair = (KeyValuePair)element;
    displayKey(keyValuePair);
    displayValue(keyValuePair);
    return success;
}

bool equalKey(Element element1, Element key){
    KeyValuePair keyValuePair1 = (KeyValuePair)element1;
    return (isEqualKey(keyValuePair1, key));
}
bool equalPair(Element element1, Element element2) {
    KeyValuePair keyValuePair1 = (KeyValuePair) element1;
    KeyValuePair keyValuePair2 = (KeyValuePair) element2;
    return isEqualKey(keyValuePair1, getKey(keyValuePair2));
}

hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber){
    if(hashNumber <= 0 || copyKey == NULL || freeKey == NULL || printKey == NULL|| copyValue == NULL || freeValue == NULL|| printValue == NULL || equalKey ==NULL || transformIntoNumber == NULL ){
        return NULL;
    }
    hashTable hash = (hashTable)malloc(sizeof (struct hashTable_s));
    if (hash == NULL){
        return NULL;
    }
    hash->hashSize = hashNumber;
    //array of linkedLists
    hash->array = (LinkedList*)malloc(sizeof(LinkedList)*hashNumber);
    if(hash->array == NULL){
        return NULL;
    }
    hash->transformIntoNumber = transformIntoNumber;
    hash->equalKey = equalKey;
    hash->printValue = printValue;
    hash->freeValue = freeValue;
    hash->copyValue = copyValue;
    hash->copyKey = copyKey;
    hash->printKey = printKey;
    hash->freeKey = freeKey;
    // start Null to each sell of the array, to know if it already been mapped.
    for(int i =0; i<hashNumber; i++){
        hash->array[i] = NULL;
    }
    return hash;
}

status addToHashTable(hashTable hash, Element key,Element value){
    if(hash == NULL|| key ==NULL|| value == NULL){
        return failure;
    }
    //create and insert the elements to KeyValuePair.
    KeyValuePair keyValuePair = createKeyValuePair(key, hash->copyKey, hash->freeKey, hash->printKey, hash->equalKey, value, hash->copyValue, hash->freeValue, hash->printValue);
    if(keyValuePair == NULL){
        return MemoryProblem;
    }
    // find where to maaped the pair.
    int index = hash->transformIntoNumber(key);
    index = index % hash->hashSize;
    //if this cell never been mapped before.
    if(hash->array[index] == NULL){
        hash->array[index] = createLinkedList(copyPair,freePair,printPair,equalPair,equalKey);
    }
    if(hash->array[index]==NULL){
    	return MemoryProblem;
    }
    //add this pair to the linked List.
    if(appendNode(hash->array[index],keyValuePair) == MemoryProblem){
    	return MemoryProblem;
    }
    return success;

}

status destroyHashTable(hashTable hash){
    if (hash == NULL){
        return failure;
    }
    //clean each linked list.
    for (int i = 0; i < hash->hashSize; i++){
        destroyList(hash->array[i]);

    }
    free(hash->array);
    free(hash);
    //use the list to find and return the value element
    return success;
}
Element lookupInHashTable(hashTable hash, Element key){
    if(hash == NULL || key == NULL){
        return NULL;
    }
    //fined by the place the key should be mapped to.
    int index = hash->transformIntoNumber(key);
    index = index % hash->hashSize;
    if(hash->array[index] == NULL){
        return NULL;
    }
    return getValue(searchByKeyList(hash->array[index],key));
}

status removeFromHashTable(hashTable hash, Element key){
    if(hash == NULL || key == NULL){
        return failure;
    }
    //fined by the place the key should be mapped to.
    int index = hash->transformIntoNumber(key);
    index = index % hash->hashSize;
    if(hash->array[index] == NULL) {
        return failure;
    }
    //use the list to delete.
    KeyValuePair del_KVP = searchByKeyList(hash->array[index],key);
    return deleteNode(hash->array[index],del_KVP);
}

status displayHashElements(hashTable hash){
    if(hash == NULL){
        return failure;
    }
    //print every linked list by the array order.
    for(int i = 0; i < hash->hashSize; i++){
        if(hash->array[i] != NULL){
            displayList(hash->array[i]);
        }
    }
    return success;
}
