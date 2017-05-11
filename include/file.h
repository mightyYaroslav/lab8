//
// Created by Yaroslav Bay on 10.05.17.
//

/** @file
 *  @brief functions to compute files
 */

#ifndef LAB8_FILE_H
#define LAB8_FILE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "list.h"
#include "jansson.h"


/**
 * @typedef File shotrcut for struct File
 */
typedef struct File File;

/** @struct File
 *  @brief defines File data type
 */
struct File {
    size_t size;
    char name[255];
    char content[10000];
};

/**
 * @brief creates new File structure based on file contents
 * @param path - file path
 * @return File structure (empty struct if error occured)
 */
File File_read(const char * path);

/**
 * @brief converts File structure to Json object
 * @param self - pointer to File struct
 * @return pointer to json object
 */
json_t * File_toJson(File * self);

/**
 * @brief retrieves the list of numbers on odd positions
 * @param self  - pointer to File structure to read
 * @return list of numbers
 */
List * numbersUnpairPos(File * self);

/**
 * @brief wrapper function for numbers convertion
 * @details used in List_toJson function
 * @param num - void pointer which need to be converted as number
 * @return json integer value
 */
json_t * numbersToJson(void * num);

#endif //LAB8_FILE_H
