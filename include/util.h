//
// Created by Yaroslav Bay on 10.05.17.
//

/**
 * @file
 * @brief utility functions
 */
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#ifndef LAB8_UTIL_H
#define LAB8_UTIL_H

/**
 * @brief checks if the string contains of numbers only
 * @param str - string to check
 * @return 1 - if string contains only numbers,
 * 0 - otherwise
 */
int is_number(const char * str);

/**
 * @brief lowercased version of string
 * @param str - base string
 * @param out - pointer where output will be stored
 * @return out pointer
 */
char * str_to_lower(const char * str, char * out);

/**
 * @brief removes junk
 * @details removes all special characters used in url while replacing %20 with spaces
 * @param src - base string
 * @param dest - pointer to output
 * @return output pointer
 */
char * removeJunk(const char * src, char * dest);

/**
 * @brief copies the string
 * @details copy is made from specified index to anothe specified index
 * @param src - source string
 * @param dest - pointer to store output
 * @param from - from index
 * @param to - to index
 */
void strftcpy(const char * src, char * dest, int from, int to);

/**
 * @brief substring
 * @param s - source string
 * @param index - index from which will take substring
 * @param len - the length of substring
 * @param out - output pointer
 * @return output pointer
 */
char * substr(const char * s, int index, int len,  char * out);

/**
 * @brief splits string
 * @details splits string into array of strings with memory allocated on heap
 * should be cleaned up with free_splitter function
 * @param s - source string
 * @param splitter - splitter character
 * @param count - pointer to number indicating strings amount
 * @return strings array
 */
char ** split(const char * s, char splitter, int * count);

/**
 * @brief cleans up after split
 * @param arr - array of strings to clean
 * @param sz - number of strings
 */
void free_splitted(char ** arr, int sz);

#endif //LAB8_UTIL_H
