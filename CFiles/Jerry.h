//
// Created by dvir on 12/23/22.
//

#ifndef UNTITLED2_JERRY_H
#define UNTITLED2_JERRY_H
/*
 * Jerry.h
 *
 *  Created on: 25 Nov 2022
 *      Author: dvir
 */


#include "Defs.h"


//planet object contain name, and 3 coordinates;

typedef struct Planet_t
{
    char *name;
    double x;
    double y;
    double z;

}Planet;


// origin contain planet object(not a copy) and dimension.
typedef struct Origin_t
{
    Planet *planet;
    char *dimention;
}Origin;


// PhysicalCharacteristics object contain name and value of this PhysicalCharacteristics.
typedef struct PhysicalCharacteristics_t {
    char *name;
    double value;
}PhysicalCharacteristics;


// jerry object contain origin and PhysicalCharacteristics objects, id string, and numbers that represent happiness and numbers of PhysicalCharacteristics.
typedef struct Jerry_t
{
    char *id;
    int happy;
    Origin *origin;
    //pointer to pointers of jerry's PhysicalCharacteristics.
    PhysicalCharacteristics **character_arr;
    int char_num;
}Jerry;


// create jerry object,
//gets id, dimension name, planet object and int for value of happiness.
//deep copy the id and dimension name.
//returns pointer to the new jerry.
Jerry* create_jerry(char *id, int happiness, Planet *planet, char *dimention);

// create planet object,
//gets name, and the 3 coordinates.
//deep copy the name.
//returns pointer to the new planet.
Planet* create_planet(char *name, double x, double y, double z);

// create PhysicalCharacteristics object,
//gets name, and his value.
//deep copy the name.
//returns pointer to the new PhysicalCharacteristics.
PhysicalCharacteristics* create_PhysicalCharacteristics(char *name, double value);

// create origin object,
//gets dimension name, and planet object.
//deep copy the dimension name.
//returns pointer to the new planet.
Origin* create_origin(Planet *planet, char *dimention);

// gets pointer to jerry and name of PhysicalCharacteristics.
//return true if jerry have this PhysicalCharacteristics else return false.
bool in_jerry(Jerry *jerry, char *p_c);

//gets pointer to jerry and PhysicalCharacteristics object
//add this PhysicalCharacteristics to jerry.
status add_characteristic(Jerry *jerry, PhysicalCharacteristics *p_c);

// gets pointer to jerry and name of PhysicalCharacteristics.
// delete the PhysicalCharacteristics that have similar name from jerry.
// if the PhysicalCharacteristics does'nt found, or bad argument return failure .
status del_characteristic(Jerry *jerry, char *p_c);

// gets pointer to jerry
// print all jerry information
//// if got bad argument return failure .
status print_jerry(Jerry *jerry);

//// gets pointer to planet
// print all planet information
//// if got bad argument return failure .
status print_planet(Planet *planet);

//gets pointer to planet/
//cleen and free planet from memory.
//return success if complete.
status destroy_planet(Planet * planet);

//gets pointer to origin
//cleen and free origin from memory.
//return success if complete.
status destroy_origin(Origin *origin);

//gets pointer to physicalCharacteristics
//cleen and free physicalCharacteristics from memory.
//return success if complete.
status destroy_physicalCharacteristics(PhysicalCharacteristics *p_c);

//gets pointer to jerry
//cleen and free jerry from memory.
//return success if complete.
status destroy_jerry(Jerry *jerry);


#endif //UNTITLED2_JERRY_H
