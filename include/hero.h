//
// Created by Yaroslav Bay on 10.05.17.
//

/**
 * @file
 * @brief contains Hero structure and functions
 * @details functions manipulate with single Hero structure
 * and with a list of heroes
 */
#include <string.h>
#include "jansson.h"
#include "list.h"
#include "util.h"

#ifndef LAB8_HERO_H
#define LAB8_HERO_H


/**
 * @typedef Hero shortcut for struct Hero
 */
typedef struct Hero Hero;

/**
 * @struct Hero
 * @brief describes a film hero
 */
struct Hero {
    long id;
    char name[100];
    char film[100];
};

/**
 * @brief converts hero structure to Json object
 * @param self - pointer to Hero structure
 * @return Json object
 */
json_t * Hero_toJson(Hero * self);

/**
 * @brief retrieves copy of the Hro structure
 * @details used while adding to filtered list
 * @param self - pointer to Hero structure
 * @return newly created Hero with same fields
 */
Hero * Hero_copy(Hero * self);

/**
 * @brief generates list of heros
 * @param quantity - number of heros
 * @return list of heros
 */
List * generateHeroes(unsigned quantity);

/**
 * @brief filters list of heros
 * @details creates new list based on key-value pair
 * @param phead - pointer to the head of heroes list
 * @param key - the key upon which list will be filtered
 * @param value - the value of the key
 * @return filtered list
 */
List * filterHeroes(List * phead, const char * key, const char * value);

#endif //LAB8_HERO_H
