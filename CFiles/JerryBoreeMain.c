//
// Created by dvir on 12/23/22.
//
//finish =)

/*
 ============================================================================
 Name        : work2.c
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
//dvir

#include <stdio.h>
#include <stdlib.h>
#include "Jerry.h"
#include <string.h>
#include "Defs.h"
#include "MultiValueHashTable.h"
#include "HashTable.h"
#include "LinkedList.h"

// functions we need for the hash that wiil be use string as element.
Element copyString(Element element){
    if(element == NULL){
        return NULL;
    }
    char *elem = (char*) element;
    char *str = (char *)malloc(sizeof (char)* strlen(elem)+1);
    strcpy(str, elem);
    return str;
}

status freeString(Element element){
    if(element == NULL){
        return failure;
    }
    char *elem = (char*) element;
    free(elem);
    return success;
}

status printString(Element element){
    if(element == NULL){
        return failure;
    }
    char *elem = (char*) element;
    printf("%s : \n", elem);
    return success;
}

bool equalString(Element element1, Element element2){
    if(element1 == NULL || element2 ==NULL){
        return false;
    }
    char *elem1 = (char*) element1;
    char *elem2 = (char*) element2;
    if(strcmp(elem1, elem2) == 0){
        return true;
    }
    return false;
}

int transformString(Element element){
    if(element == NULL){
        return -1;
    }
    char *elem = (char*) element;
    return atoi(elem);
}

//functions that we need to send to the hash using Jerry as element.

//there is only one jerry whith the same id and can not be copied.
Element copyJerry(Element element){

    return element;
}
//we never deep copy jerry so we dont need to free him.
status freeJerry(Element element){

    return success;
}
//use in the linked list of jerries.
status destroyJerry(Element element){
    if(element == NULL){
        return failure;
    }
    Jerry *jerry = (Jerry*)element;
    return destroy_jerry(jerry);
}

status printJerry(Element element){
    if (element == NULL){
        return failure;
    }
    Jerry *jerry = (Jerry*)element;
    return print_jerry(jerry);
}

bool equalJerry(Element element1, Element element2){
    if(element1 == NULL|| element2 ==NULL){
        return false;
    }
    Jerry *jerry1 = (Jerry*)element1;
    Jerry *jerry2 = (Jerry*)element2;
    if(strcmp(jerry1->id, jerry2->id)==0){
        return true;
    }
    return false;
}

bool keyInJerry(Element element, Element key){
    if(element ==NULL || key == NULL){
        return false;
    }
    Jerry *jerry = (Jerry*)element;
    char* id = (char*)key;
    if(strcmp(jerry->id, id) == 0){
        return true;
    }
    return false;
}

//free all memory and exit in case of memory problem.
void memoProblem(MultiValueHashTable m_hash, hashTable hash, LinkedList list, Planet** array, int num){
	destroyHashTable(hash);
	destroyMultiValueHashTable(m_hash);
	destroyList(list);
	for (int i = 0; i < num; i++) {
		destroy_planet(array[i]);
	            }
}
int main(int argc, char* argv[]) {


// upper strings.;

    char mystring [100];


    int num_planets;//number of planets
    num_planets = atoi(argv[1]);

//array of all planets
    Planet *planets[num_planets];
    char *planets_names[num_planets];

    int save;
    //hash of jerries mapped by there id, the key is the id of jerry and the value is the Jerry object.
    hashTable idHash = createHashTable(copyString, freeString, printString, copyJerry, freeJerry, printJerry, equalString, transformString, 29);
    if (idHash == NULL) {
	   fprintf(stderr, "Memory Problem");
    return 1;}

    //multi hash of jerry characters the key is the name of the character and the values is all jerries who have that characteristic.
    MultiValueHashTable characterHash = createMultiValueHashTable(copyString, freeString, printString, copyJerry, freeJerry, printJerry, equalString, transformString, 37, equalJerry, keyInJerry);
    if (characterHash == NULL) {
   	   fprintf(stderr, "Memory Problem");
       return 1;}
    int py_num = 0;
    char* jerry_id;
    char *jerry_dimention;
    char *physical_char;
    int finish = 0;
    //linked list of all jerries that in the system.
    LinkedList jerryList = createLinkedList(copyJerry, destroyJerry, printJerry, equalJerry, keyInJerry);
    if (jerryList == NULL) {
      	   fprintf(stderr, "Memory Problem");
          return 1;}


    // open the file
    FILE *f ;

    // if there was an error
    f = fopen (argv[2], "r");
    if (f == NULL) perror ("Error opening file");
    else {
        // while there are lines to read.

        while (finish != 1) {
            if(fgets(mystring, 100, f)==NULL){
                finish=1;
            }
            //the start of the planets.
            if (strcmp(strtok(mystring, "s"), "Planet") == 0) {
                for (int i = 0; i < num_planets; i++) {
                    fgets(mystring, 100, f);
                    strtok(mystring, ",");
                    //add planet name to the planet name array.
                    planets_names[i] = (char *) malloc(sizeof(char) * (strlen(mystring) )+1);
					if (planets_names[i] == NULL) {
						fprintf(stderr, "Memory Problem");
						return 1;}

                    strcpy(planets_names[i], mystring);
                    float x;
                    x = atof(strtok(NULL, ","));
                    float y;
                    y = atof(strtok(NULL, ","));
                    float z;
                    z = atof(strtok(NULL, ","));
                    //add new planet to the planet array.
                    planets[i] = create_planet((planets_names[i]), x, y, z);
                    if(planets[i] == NULL){
                    	fprintf(stderr, "Memory Problem");
							return 1;
                    }

                }
            }
            //start of the jerries.
            if (strcmp(strtok(mystring, "s"), "Jerrie") == 0) {
                if(fgets(mystring, 100, f) == NULL){
                    finish =1;
                }

                while (finish!=1) {
                    //create all jerrys.
                    strtok(mystring, ",");
                    jerry_id = (char *) malloc(sizeof(char) * (strlen(mystring)) + 1);
                    if (jerry_id == NULL) {
                        fprintf(stderr, "Memory Problem");
						return 1;
                    }
                    strcpy(jerry_id, mystring);
                    // save the dimension .
                    char *dem = strtok(NULL, ",");
                    jerry_dimention = (char *) malloc(sizeof(char) * (strlen(dem) + 1));
                    if (jerry_dimention == NULL) {
                        fprintf(stderr, "Memory Problem");
                        		return 1;
                    }
                    strcpy(jerry_dimention, dem);
                    char *planet_n = strtok(NULL, ",");
                    //find the planet in the planet array.
                    for (int j = 0; j < num_planets; j++) {
                        if (strcmp(planet_n, planets[j]->name) == 0) {
                            save = j;
                        }
                    }
                    float happiness = atof(strtok(NULL, ","));
                    // create new jerry and add him to the jerry list and the jerry hash.
                    Jerry *jerry;
                    jerry = create_jerry(jerry_id, happiness, planets[save], jerry_dimention);
                    free(jerry_dimention);
                    if (jerry == NULL) {
                        fprintf(stderr, "Memory Problem");
                    }
                    addToHashTable(idHash, jerry_id, jerry);
                    appendNode(jerryList,jerry);
                    free(jerry_id);
                    if(fgets(mystring, 100, f) == NULL){
                        finish=1;
                    }
                    //add each jerry his characteristics.
                    while (strcspn(mystring, "\t" ) < 1  ) {
                        strtok(mystring, ":");
                        //save the names.
                        physical_char = (char *) malloc(sizeof(char) * (strlen(mystring)) + 1);
                        if (physical_char == NULL) {
                            fprintf(stderr, "Memory Problem");
                            return 1;
                        }
                        strcpy(physical_char, mystring + 1);
                        float val;
                        val = atof(strtok(NULL, ","));
                        //create and add the characteristic to jerry.
                        PhysicalCharacteristics *py = create_PhysicalCharacteristics(physical_char, val);

                        if (py == NULL) {
                            fprintf(stderr, "Memory Problem");
                            return 1;
                        }
                        if (add_characteristic(jerry, py) == MemoryProblem) {
                            fprintf(stderr, "Memory Problem");
                            return 1;
                        }
                        //add the jerry by these characteristic to the characteristic multi hash.
                        if(addToMultiValueHashTable(characterHash, physical_char, jerry)==MemoryProblem){
                        	fprintf(stderr, "Memory Problem");
								return 1;
                        }

                        free(physical_char);
                        py_num++;
                        if(fgets(mystring, 100, f) == NULL){
                            finish =1;
                            break;
                        }

                    }
                }
            }
        }
        fclose(f);
//free all the arrays we no longer use.


}
    //clean all the planet name we no longer need
for (int i = 0; i < num_planets; i++) {
        free(planets_names[i]);}

    char choise[300] ;
    char *p1, *p2, *p3, buffer[300];
    int ch = 1;
    int in_p = 0;
    int val;
    int sw = 1;
    Jerry *jerry ;
    PhysicalCharacteristics *pc;
    LinkedList linkedList;
    //find memory problems
    status stat1;
    status stat2;
    while( ch != 0 ) {
   printf("Welcome Rick, what are your Jerry's needs today ? \n");
   printf("1 : Take this Jerry away from me \n");
   printf("2 : I think I remember something about my Jerry \n");
   printf("3 : Oh wait. That can't be right \n");
   printf("4 : I guess I will take back my Jerry now \n");
   printf("5 : I can't find my Jerry. Just give me a similar one \n");
   printf("6 : I lost a bet. Give me your saddest Jerry \n");
   printf("7 : Show me what you got \n");
   printf("8 : Let the Jerries play \n");
   printf("9 : I had enough. Close this place \n");

   //find if valid input
    scanf("%s", choise );
    if(strlen(choise) > 1){
        ch = 10;
    } else{
        ch = atoi(choise);
    }



    switch( ch ){

    case 1:
    	//ad new jerry to the system
        printf("What is your Jerry's ID ? \n");
        scanf("%s", buffer );
        p1 = (char *) malloc(strlen(buffer)+1);
        if(p1 == NULL){
            fprintf(stderr,"Memory Problem");
            memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            return 1;
        }
        strcpy(p1, buffer);
        jerry = lookupInHashTable(idHash,p1);
        if(jerry != NULL) {
            printf("Rick did you forgot ? you already left him here ! \n");
            free(p1);
            break;
        }
        printf("What planet is your Jerry from ? \n");
        scanf("%s", buffer );
        p2 = (char *) malloc(strlen(buffer)+1);
        if(p2 == NULL){
            fprintf(stderr,"Memory Problem");
            memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            free(p2);
            return 1;
        }
        strcpy(p2, buffer);
        in_p = -1;
        //find planet
        for(int i =0; i< num_planets; i++){
            if (strcmp(p2, planets[i]->name) == 0){
                in_p = i;
            }
        }
        //planet does not found.
        if (in_p ==-1){
            printf("%s is not a known planet ! \n", p2);
            free(p1);
            free(p2);
            break;
        }
        printf("What is your Jerry's dimension ? \n");
        scanf("%s", buffer );
        p3 = (char *) malloc(strlen(buffer)+1);
        if(p3 == NULL){
            fprintf(stderr,"Memory Problem");
            memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            free(p2);
            free(p3);
            return 1;
        }
        strcpy(p3, buffer);
        printf("How happy is your Jerry now ? \n");
        scanf("%d", &val );
        //create jerry and add him to all the hash tables.
        Jerry *jerry1 = create_jerry(p1, val, planets[in_p], p3);
        if (jerry1 == NULL){
        	fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
        	free(p1);
			free(p2);
			free(p3);
			return 1;
}
        stat1 = addToHashTable(idHash,p1, jerry1);
        stat2 = appendNode(jerryList,jerry1);
        if(stat1 == MemoryProblem || stat2 == MemoryProblem){
        	fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
			free(p1);
			free(p2);
			free(p3);
			return 1;
        }
        printJerry(jerry1);
        free(p1);
        free(p2);
        free(p3);
        break;


    case 2:
    	//add characteristic to jerry.
        printf("What is your Jerry's ID ? \n");
        scanf("%s", buffer );
        p1 = (char *) malloc(strlen(buffer)+1);
        if(p1 == NULL){
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            fprintf(stderr,"Memory Problem");
            free(p1);
            return 1;
        }
        strcpy(p1, buffer);
        jerry = lookupInHashTable(idHash,p1);
        if(jerry == NULL) {
            printf("Rick this Jerry is not in the daycare ! \n");
            free(p1);
            break;
        }
        printf("What physical characteristic can you add to Jerry - %s ? \n", p1);
        scanf("%s", buffer );
        p2 = (char *) malloc(strlen(buffer)+1);
        if(p2 == NULL){
            fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            free(p2);
            return 1;
        }
        strcpy(p2, buffer);
        if(in_jerry(jerry, p2) == true){
            printf("The information about his %s already available to the daycare ! \n", p2);
            free(p1);
            free(p2);
            break;
        }
        printf("What is the value of his %s ? \n", p2);
        scanf("%d", &val );
        pc = create_PhysicalCharacteristics(p2, val);
        //add jerry to the vash of characteristic in whith the new characteristic
        stat1 = add_characteristic(jerry,pc);
        stat2 = addToMultiValueHashTable(characterHash, p2, jerry);
        if(stat1 == MemoryProblem || stat2 == MemoryProblem){
			fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
			free(p1);
			free(p2);
			free(p3);
			return 1;
		}
        displayMultiValueHashElementsByKey(characterHash,p2);
            free(p1);
            free(p2);
        break;


    case 3:
    	//delete charcteristic from jerry
        printf("What is your Jerry's ID ? \n");
        scanf("%s", buffer );
        p1 = (char *) malloc(strlen(buffer)+1);
        if(p1 == NULL){
            fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            return 1;
        }
        strcpy(p1, buffer);
        jerry = lookupInHashTable(idHash,p1);
        if(jerry == NULL) {
            printf("Rick this Jerry is not in the daycare ! \n");
            free(p1);
            break;
        }
        printf("What physical characteristic do you want to remove from Jerry - %s ? \n", p1);
        scanf("%s", buffer );
        p2 = (char *) malloc(strlen(buffer)+1);
        if(p2 == NULL){
            fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            free(p2);
            return 1;
        }
        strcpy(p2, buffer);
        if(in_jerry(jerry, p2) == false){
            printf("The information about his %s not available to the daycare ! \n", p2);
            free(p1);
            free(p2);
            break;
        }
        del_characteristic(jerry,p2);
        removeFromMultiValueHashTable(characterHash, p2, p1);
        printJerry(jerry);
        free(p1);
        free(p2);
        break;

    case 4:
    	//take out jerry from the daycare
        printf("What is your Jerry's ID ? \n");
        scanf("%s", buffer );
        p1 = (char *) malloc(strlen(buffer)+1);
        if(p1 == NULL){
            fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            return 1;
        }
        strcpy(p1, buffer);
        jerry = lookupInHashTable(idHash,p1);
        if(jerry == NULL) {
            printf("Rick this Jerry is not in the daycare ! \n");
            free(p1);
            break;
        }
        //remove him from all the ADTs
        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
        removeFromHashTable(idHash,p1);
        for(int i = 0; i < jerry->char_num; i++){
            removeFromMultiValueHashTable(characterHash, jerry->character_arr[i]->name, p1);
        }
        deleteNode(jerryList, jerry);
        free(p1);
        break;

    case 5:
    	//take out from the daycare the jerry with characteristic that closestby the value
        printf("What do you remember about your Jerry ? \n");
        scanf("%s", buffer );
        p1 = (char *) malloc(strlen(buffer)+1);
        if(p1 == NULL){
            fprintf(stderr,"Memory Problem");
			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
            free(p1);
            return 1;
        }
        strcpy(p1, buffer);
        linkedList = lookupInMultiValueHashTable(characterHash,p1);
        if(linkedList == NULL){
            printf("Rick we can not help you - we do not know any Jerry's %s ! \n", p1);
            free(p1);
            break;
        }
        printf("What do you remember about the value of his %s ? \n", p1);
        scanf("%d", &val );
        double curr;
        double min = -1;
        Jerry *closest_jerry;
        for(int i = 1; i <= getLengthList(linkedList); i++){
            jerry = getDataByIndex(linkedList,i);
            for (int j = 0; j < jerry->char_num; j++){
                if(strcmp(p1, jerry->character_arr[j]->name) == 0){
                    if(jerry->character_arr[j]->value >= val){
                        curr = jerry->character_arr[j]->value - val;
                    } else{
                        curr = val - jerry->character_arr[j]->value;
                    }
                    if (curr < min){
                        closest_jerry = jerry;
                        min = curr;
                    }
                    if(min == -1){
                        closest_jerry = jerry;
                        min = curr;
                    }
                    break;
                }
            }
        }
        printf("Rick this is the most suitable Jerry we found : \n");
        printJerry(closest_jerry);
        removeFromHashTable(idHash,closest_jerry->id);
        removeFromMultiValueHashTable(characterHash, p1, closest_jerry->id);
        deleteNode(jerryList,closest_jerry);
        free(p1);
        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
        break;


    case 6:
    	//take out from the dycare the sadest jerry
        if(getLengthList(jerryList) == 0){
            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
            break;
        }
        Jerry *saddest_jerry;
        int saddest = 101;
        for(int i = 1; i <= getLengthList(jerryList); i++){
            jerry = getDataByIndex(jerryList,i);
            if(jerry->happy < saddest){
                saddest_jerry = jerry;
                saddest= saddest_jerry->happy;
            }
        }
        printf("Rick this is the most suitable Jerry we found : \n");
        removeFromHashTable(idHash,saddest_jerry->id);
        for(int j = 0; j < saddest_jerry->char_num; j++){
            removeFromMultiValueHashTable(characterHash, saddest_jerry->character_arr[j]->name, saddest_jerry->id);
        }
        print_jerry(saddest_jerry);
        deleteNode(jerryList,saddest_jerry);
        printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
        break;

    case 7 :

         sw=1;
        while (sw != 0){
            printf("What information do you want to know ? \n");
            printf("1 : All Jerries \n");
            printf("2 : All Jerries by physical characteristics \n");
            printf("3 : All known planets \n");
            scanf("%s", choise );
            if(strlen(choise) > 1){
                    sw = 10;
                } else{
                    sw = atoi(choise);
                }
            switch( sw ){
                case 1:
                	//print all jerries
                    if (getLengthList(jerryList) == 0){
                        printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
                    }
                    displayList(jerryList);
                    sw = 0;
                    break;

                case 2:
                	//print all jerries with the characteristics.
                    printf("What physical characteristics ? \n");
                    scanf("%s", buffer );
                    p1 = (char *) malloc(strlen(buffer)+1);
                    if(p1 == NULL){
                        fprintf(stderr,"Memory Problem");
            			memoProblem(characterHash, idHash, jerryList,planets , num_planets);
                        free(p1);
                        sw = 0;
                        return 1;
                    }
                    strcpy(p1, buffer);
                    linkedList = lookupInMultiValueHashTable(characterHash,p1);
                    if(linkedList == NULL){
                    printf("Rick we can not help you - we do not know any Jerry's %s ! \n", p1);
                    sw = 0;
                    free(p1);
                    break;
                    }
                    printf("%s : \n", p1);
                    displayList(linkedList);
                    sw =0;
                    free(p1);
                    break;

                case 3:
                	//print all planets
                    for(int i =0 ; i< num_planets; i++){
                        print_planet(planets[i]);
                    }
                    sw=0;
                    break;
                default:
                    printf("Rick this option is not known to the daycare ! \n");
                    sw =0;
                    break;
            }
        }
        break;

    case 8:
    	//add or sub the jerries happiness by the activity
        if(getLengthList(jerryList) == 0){
            printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
            break;
        }
        sw=1;
        while (sw != 0){
            printf("What activity do you want the Jerries to partake in ? \n");
            printf("1 : Interact with fake Beth \n");
            printf("2 : Play golf \n");
            printf("3 : Adjust the picture settings on the TV \n");
            scanf("%s", choise );
            sw = atoi(choise);
            switch( sw ) {

                case 1:
                    for (int i = 1; i <= getLengthList(jerryList); i++) {
                        jerry = getDataByIndex(jerryList, i);
                        if (jerry->happy >= 20) {
                            if (jerry->happy >= 85) {
                                jerry->happy = 100;
                            } else {
                                jerry->happy += 15;
                            }
                        } else {
                            if (jerry->happy <= 5) {
                                jerry->happy = 0;
                            } else {
                                jerry->happy -= 5;
                            }
                        }
                    }
                    sw = 0;
                    printf("The activity is now over ! \n");
						displayList(jerryList);
                    break;
                case 2:
                    for (int i = 1; i <= getLengthList(jerryList); i++) {
                        jerry = getDataByIndex(jerryList, i);
                        if (jerry->happy >= 50) {
                            if (jerry->happy >= 90) {
                                jerry->happy = 100;
                            } else {
                                jerry->happy += 10;
                            }
                        } else {
                            if (jerry->happy <= 10) {
                                jerry->happy = 0;
                            } else {
                                jerry->happy -= 10;
                            }
                        }
                    }
                    printf("The activity is now over ! \n");
						displayList(jerryList);
                    sw = 0;
                    break;


                case 3:
                    for (int i = 1; i <= getLengthList(jerryList); i++) {
                        jerry = getDataByIndex(jerryList, i);
                        if (jerry->happy >= 80) {
                            jerry->happy = 100;
                        } else {
                            jerry->happy += 20;
                        }
                    }
                    sw = 0;
                    printf("The activity is now over ! \n");
					displayList(jerryList);
                    break;
                default:
                    printf("Rick this option is not known to the daycare ! \n");
                    sw=0;
                    break;
            }
            }

            break;


        case 9:
        	//destroy avery memory and ADT we use.
            destroyHashTable(idHash);
            destroyMultiValueHashTable(characterHash);
            destroyList(jerryList);
            for (int i = 0; i < num_planets; i++) {
                destroy_planet(planets[i]);
            }
            printf("The daycare is now clean and close ! \n");
            ch = 0;
            break;


        default:
    //invalid input.
        printf("Rick this option is not known to the daycare ! \n");
        ch=1;
        break;

        }
    }

    return 0;
}
//int num_planets, int num_jerry, char* argv[]
