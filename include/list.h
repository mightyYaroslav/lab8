/**
 * @file
 * @brief contains list realization
 * @details based on linked list
 */

#ifndef list_h
#define list_h

#include <stdlib.h>
#include <assert.h>
#include "jansson.h"

/**
 * @struct List
 * @brief describes a single node of the list
 */
typedef struct List {
    void * data;
    struct List * next;
} List;

/**
 * @brief creates new list
 * @return NULL pointer
 */
List * List_new();

/**
 * @brief frees memory allocated for list
 * @details calls onFree function for every node
 * before deleteing the node itself
 * @param phead - pointer to the head of the list
 * @param onFree - function used to free value inside list
 */
void List_free(List * phead, void (*onFree)(List *));


/**
 * @brief adds new element to list
 * @param phead - double pointer to the head of the list
 * @param val - pointer to value to be added
 */
void List_add(List ** phead, void * val);

/**
 * @brief deletes element from the end of list
 * @param phead - pointer to the head of the list
 * @param onFree - function called to free data of the node before freeing the node
 */
void List_pop(List ** phead, void (*onFree)(List *));


/**
 * @brief inserts value into specified position
 * @param phead - pointer to the head of the list
 * @param index - index showing where value should be placed
 * @param val - pointer to value itself
 */
void List_insert(List ** phead, size_t index, void * val);

/**
 * @brief removes the node on specified index
 * @param phead - pointer to the head of the list
 * @param index - the index of the node
 * @param onFree - function to free the node data
 */
void List_remove(List ** phead, size_t index, void (*onFree)(List *));

/**
 * @param phead - pointer to the head of the list
 * @return number of elements in the list
 */
size_t List_count(List * phead);

/**
 * @brief sorts the list
 * @param phead - pointer to the head of the list
 * @param cmp - function used to compare data of nodes
 * return 1 if first node is 'bigger'
 * return 0 if nodes are 'equal'
 * return -1 if first node if 'smaller'
 */
void List_sort(List ** phead, int (*cmp)(List *, List*));

/**
 * @brief create the copy of the list
 * @param src - pointer to the head of source list
 * @param dest - double pointer to the head of the destination list
 * @param create_copy - function to allocate memory for node data
 * @param onFree - function used to free node data
 */
void List_copy(List * src, List ** dest, void * (*create_copy)(void *), void (*onFree)(List *));

/**
 * @param phead - pointer to the head of the list
 * @param dataToJson - function used to convert list data to json
 * @return Json array
 */
json_t * List_toJson(List * phead, json_t * (*dataToJson)(void *));

#endif
