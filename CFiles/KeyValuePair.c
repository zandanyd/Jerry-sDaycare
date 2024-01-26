//
// Created by dvir on 12/19/22.
//
#include "KeyValuePair.h"
//contain key and value elements and functions for each element
struct KeyValuePair_t{
    Element key;
    Element value;
    CopyFunction key_copyFunction;
    FreeFunction key_freeFunction;
    PrintFunction key_printFunction;
    EqualFunction key_equalFunction;
    CopyFunction value_copyFunction;
    FreeFunction value_freeFunction;
    PrintFunction value_printFunction;
    EqualFunction value_equalFunction;
};
KeyValuePair createKeyValuePair(Element key,CopyFunction key_copyFunction, FreeFunction key_freeFunction,
                                PrintFunction key_printFunction,EqualFunction key_equalFunction, Element value,
                                CopyFunction value_copyFunction, FreeFunction value_freeFunction,
                                PrintFunction value_printFunction){
    KeyValuePair keyValuePair = (KeyValuePair)malloc(sizeof(struct KeyValuePair_t));
    if(keyValuePair == NULL){
        return NULL;
    }

    keyValuePair->key_copyFunction = key_copyFunction;
    keyValuePair->key_equalFunction = key_equalFunction;
    keyValuePair->key_freeFunction = key_freeFunction;
    keyValuePair->key_printFunction = key_printFunction;
    keyValuePair->key = key_copyFunction(key);
    keyValuePair->value = value_copyFunction(value);
    keyValuePair->value_copyFunction = value_copyFunction;
    keyValuePair->value_freeFunction = value_freeFunction;
    keyValuePair->value_printFunction = value_printFunction;
    return keyValuePair;
}
status destroyKeyValuePair(KeyValuePair keyValuePair){
    if(keyValuePair == NULL){
        return failure;
    }
    //use the user free functions
    keyValuePair->key_freeFunction(keyValuePair->key);
    keyValuePair->value_freeFunction(keyValuePair->value);
    free(keyValuePair);
    return success;
}

status displayValue(KeyValuePair keyValuePair){
    if(keyValuePair == NULL){
        return failure;
    }
    //use the user print functions
    keyValuePair->value_printFunction(keyValuePair->value);
    return success;
}

status displayKey(KeyValuePair keyValuePair){
    if(keyValuePair == NULL){
        return failure;
    }
    //use the user print functions
    keyValuePair->key_printFunction(keyValuePair->key);
    return success;
}

Element getValue(KeyValuePair keyValuePair){
    if(keyValuePair == NULL) {
        return NULL;
    }
    return keyValuePair->value;
}

Element getKey(KeyValuePair keyValuePair){
    if(keyValuePair == NULL) {
        return NULL;
    }
    return keyValuePair->key;
}

bool isEqualKey(KeyValuePair keyValuePair, Element key){
    if (keyValuePair == NULL || key == NULL){
        return false;
    }
    return keyValuePair->key_equalFunction(keyValuePair->key, key);
}

KeyValuePair copyKeyValuePair(KeyValuePair Pair){
	//create new pair with the same data
    return createKeyValuePair(Pair->key, Pair->key_copyFunction, Pair->key_freeFunction, Pair->key_printFunction,Pair->key_equalFunction,
                              Pair->value, Pair->value_copyFunction, Pair->value_freeFunction, Pair->value_printFunction);
}
