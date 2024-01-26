//
// Created by dvir on 12/23/22.
//
/*
 * Jerry.c dvir
 *
 *  Created on: 26 Nov 2022
 *      Author: dvir
 */
#include "Jerry.h"
#include "Defs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Jerry* create_jerry(char *id, int happiness, Planet *planet, char *dimention)
{
    if(id == NULL || planet == NULL || dimention == NULL){

        return NULL;
    }
    Jerry *jerry;
    jerry = (Jerry*)malloc(sizeof(Jerry));
    if (jerry == NULL){

        return NULL;
    }
    else{
        //copy of the id string we got to new string.
        jerry->id = (char*)malloc(sizeof(char)*(strlen(id))+1);
        if (jerry->id == NULL){
            return NULL;
        }
        strcpy(jerry->id,id);
        jerry->happy = happiness;
        //create the origin with the planet and name of the origin
        Origin *origin = create_origin(planet, dimention);
        jerry->origin = origin;
        //initialize empty physical-characteristic "array".
        jerry->character_arr = NULL;
        jerry->char_num = 0;
        return jerry;
    }
}
Planet* create_planet(char *name, double x, double y, double z)
{
    if(name == NULL){
        return NULL;
    }
    Planet *planet;
    planet = (Planet*)malloc(sizeof(Planet));
    if (planet == NULL){

        return NULL;
    }
    //copy of the id string we got to new string.
    planet->name = (char*)malloc(sizeof(char)*(strlen(name))+1);
    if (planet->name == NULL){
        return NULL;
    }
    strcpy((planet->name),name);
    planet->x = x;
    planet->y = y;
    planet->z = z;
    return planet;
}

PhysicalCharacteristics* create_PhysicalCharacteristics(char *name, double value)
{
    if(name == NULL){
        return NULL;
    }

    PhysicalCharacteristics *p_c;
    p_c = (PhysicalCharacteristics*)malloc(sizeof(PhysicalCharacteristics));
    if (p_c == NULL){
        return NULL;
    }
    //copy of the id string we got to new string.
    p_c->name = (char*)malloc(sizeof(char)*(strlen(name)+1));
    strcpy(p_c->name,name);
    p_c->value = value;
    return p_c;
}

Origin* create_origin(Planet *planet, char *dimention){
    if(planet== NULL || dimention == NULL){
        return NULL;
    }
    Origin *origin;
    origin = (Origin*)malloc(sizeof(Origin));
    if (origin == NULL){

        return NULL;
    }
    //copy of the id string we got to new string.
    origin->dimention = (char*)malloc(sizeof(char)*(strlen(dimention))+1);
    strcpy(origin->dimention, dimention);
    origin->planet = planet;
    return origin;
}

// find if the physical characteristic in this jerry.
bool in_jerry(Jerry *jerry, char *p_c)
{
    if(jerry == NULL || p_c == NULL){
        return false;
    }
    for(int i = 0; i < (jerry->char_num); i++ ){
        if(strcmp((jerry->character_arr)[i]->name, p_c) == 0){
            return true;
        }
    }
    return false;
}

// add characteristic to jerry, to the end of the array.
status add_characteristic(Jerry *jerry, PhysicalCharacteristics *p_c)
{
    if(jerry == NULL || p_c == NULL){

        return failure;
    }
    //add memory allocation to the characteristic array.
    jerry->character_arr = (PhysicalCharacteristics**)realloc(jerry->character_arr, ((jerry->char_num) + 1) * sizeof(PhysicalCharacteristics*));
    if (jerry->character_arr == NULL){

        return MemoryProblem;
    }
    (jerry->character_arr)[jerry->char_num] = p_c;
    // add one to the size of the array .
    jerry->char_num ++;
    return success;
}

// delete characteristic from jerry.
status del_characteristic(Jerry *jerry, char *p_c){
    if(jerry == NULL || p_c == NULL)
    {

        return failure;
    }
    if (in_jerry(jerry, p_c) == false){
        return failure;
    }
    else {
        for(int i = 0; i < (jerry->char_num); i++ ){
            // if this characteristic in jerry.
            if(strcmp((jerry->character_arr)[i]->name, p_c) == 0){
                // shift right all the characteristics from the characteristic we want to delete.
                for (int j = i; j< ((jerry->char_num)-1); j++){
                    PhysicalCharacteristics *curr = jerry->character_arr[j];
                    jerry->character_arr[j] = jerry->character_arr[j+1];
                    jerry->character_arr[j+1] = curr;
                }
            }
        }
        //delete and free the memory.
        destroy_physicalCharacteristics(jerry->character_arr[(jerry->char_num)-1]);
        jerry->character_arr = (PhysicalCharacteristics**)realloc(jerry->character_arr, ((jerry->char_num - 1)*sizeof(PhysicalCharacteristics*)));
        jerry->char_num --;
        return success;
    }
}

//print all jerry's details.
status print_jerry(Jerry *jerry){
    if (jerry == NULL){
        return failure;
    }
    printf("Jerry , ID - %s : \n", jerry->id);
    printf("Happiness level : %d \n", jerry->happy);
    printf("Origin : %s \n", jerry->origin->dimention);
    print_planet(jerry->origin->planet);

    if(jerry->char_num > 0){
        printf("Jerry's physical Characteristics available : \n\t");
        for (int i = 0; i < (jerry->char_num)-1; i++){
            printf("%s : %.2f , ", (jerry->character_arr)[i]->name, jerry->character_arr[i]->value);
        }
        printf("%s : %.2f \n", jerry->character_arr[jerry->char_num-1]->name, jerry->character_arr[jerry->char_num-1]->value);
    }
    return success;
}

//print the planet
status print_planet(Planet *planet){
    if (planet == NULL){
        return failure;
    }
    printf("Planet : %s (%.2f,%.2f,%.2f) \n", planet->name, planet->x, planet->y, planet->z);
    return success;

}


status destroy_planet(Planet * planet){
    if (planet == NULL){
        return failure;
    }
    free(planet->name);
    free(planet);
    return success;
}

status destroy_origin(Origin *origin){
    if (origin == NULL){
        return failure;
    }
    free(origin->dimention);

    free(origin);
    return success;
}

status destroy_physicalCharacteristics(PhysicalCharacteristics *p_c){
    if (p_c == NULL){
        return failure;
    }
    free(p_c->name);
    free(p_c);
    return success;
}

status destroy_jerry(Jerry *jerry){
    if(jerry == NULL){
        return failure;
    }
    free(jerry->id);
    destroy_origin(jerry->origin);

    for(int i = 0; i< jerry->char_num; i++){
        destroy_physicalCharacteristics(jerry->character_arr[i]);
    }
    free(jerry->character_arr);
    free(jerry);
    return success;
}


