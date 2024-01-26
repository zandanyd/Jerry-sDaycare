//
// Created by dvir on 12/19/22.
//
#ifndef UNTITLED2_KEYVALUEPAIR_H
#define UNTITLED2_KEYVALUEPAIR_H

#include "Defs.h"
typedef struct KeyValuePair_t *KeyValuePair;

// KeyValuePair save to elements key and value, to know how to use this elements it needs for each element free, copy, and print functions.
//in addition it require equal function for the key to compare between key elements.
//the elements that been sent to the Object will be copied by the the copy functions he got from the user.
KeyValuePair createKeyValuePair(Element key,CopyFunction key_copyFunction, FreeFunction key_freeFunction,
                                PrintFunction key_printFunction,EqualFunction key_equalFunction, Element value,
                                CopyFunction value_copyFunction, FreeFunction value_freeFunction,
                                PrintFunction value_printFunction);

//clean and free all the KeyValuePair memory, use the free function to destroy the elements as well.
status destroyKeyValuePair(KeyValuePair keyValuePair);

//print the key  using the user print element function.
status displayValue(KeyValuePair keyValuePair);

//print the value  using the user print element function.
status displayKey(KeyValuePair keyValuePair);

// return the value element of this keyValuePair.
Element getValue(KeyValuePair keyValuePair);

// return the key element of this keyValuePair.
Element getKey(KeyValuePair keyValuePair);

// return true if the keyValuePair contain this key element else false.
bool isEqualKey(KeyValuePair keyValuePair, Element key);

// copy the keyValuePair use the user copy functions.
KeyValuePair copyKeyValuePair(KeyValuePair);

#endif //UNTITLED2_KEYVALUEPAIR_H
