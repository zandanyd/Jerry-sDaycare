//
// Created by dvir on 12/22/22.
//

#ifndef UNTITLED2_MULTIVALUEHASHTABLE_H
#define UNTITLED2_MULTIVALUEHASHTABLE_H
#include "Defs.h"
typedef struct MultiValueHashTable_t *MultiValueHashTable;

//create hash that could have many values elements to the same key.
//to know how to use this elements it require for each element free, copy, equal, and print functions.
////in addition it require integer for the hash size and transform number from the key element to integer and equal by part of the element function. .
MultiValueHashTable createMultiValueHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber, EqualFunction equalValue, EqualFunction equalPart);

//clean and free all the hash memory, use the free function to destroy the elements as well.
status destroyMultiValueHashTable(MultiValueHashTable multiValueHashTable);

//add two new elements to the hash table by there key and the transform function.
//the elements will be copied by the functions they get from the user.
status addToMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element value);

//find if these key exist in the hash table
//returns the key's all values if it does and NULL if it does'nt
Element lookupInMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key);

//find the key and remove from the hash table the key's value that belong to it by the equalPart function.
status removeFromMultiValueHashTable(MultiValueHashTable multiValueHashTable, Element key, Element valuePart);

//print all the key's vales.
status displayMultiValueHashElementsByKey(MultiValueHashTable multiValueHashTable, Element key);

#endif //UNTITLED2_MULTIVALUEHASHTABLE_H
