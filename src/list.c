#include "list.h"

#define throw(msg) assert(0 && msg)

List * List_new() {
    return NULL;
}

void List_free(List * phead, void (*onFree)(List *)) {
    List * pcur = phead;
    while(phead != NULL) {
        pcur = phead;
        phead = (phead)->next;
        onFree(pcur);
        free(pcur);
    }
}

void List_add(List ** phead, void * val) {
    List * pcur = *phead;

    List * new_element = malloc(sizeof(List));
    new_element->data = val;
    new_element->next = NULL;
    if(*phead == NULL) {
        *phead = new_element;
    } else {
        while (pcur->next != NULL)
            pcur = pcur->next;
        pcur->next = new_element;
    }
}

void List_pop(List ** phead, void (*onFree)(List *)) {
    if(*phead == NULL) throw("Attempt to pop from empty list");
    else if((*phead)->next == NULL) {
        free(*phead);
        *phead = NULL;
    } else {
        List * pcur = *phead;
        while (pcur->next->next != NULL)
            pcur = (pcur)->next;
        onFree(pcur->next);
        free(pcur->next);
        pcur->next = NULL;
    }
}

void List_insert(List ** phead, size_t index, void * val) {
    if(index > List_count(*phead)) throw("Index is out of range");

    List * pcur = *phead;
    List * new_element = malloc(sizeof(List));
    new_element->data = val;

    if(index == 0) {
        new_element->next = *phead;
        *phead = new_element;
        return;
    } else {
        for (size_t i = 0; i < index - 1; i++)
            pcur = pcur->next;

        new_element->next = pcur->next;
        pcur->next = new_element;
    }
}

void List_remove(List ** phead, size_t index, void (*onFree)(List *)) {
    if(index >= List_count(*phead)) throw("Index out of range");
    if(*phead == NULL) throw("Attempt to remove from empty list");

    if(index == 0) {
        free(*phead);
        *phead = (*phead)->next;
    } else {
        List *pcur = *phead;
        for (size_t i = 0; i < index - 1; i++)
            pcur = pcur->next;
        List * nn = pcur->next->next;
        onFree(pcur->next);
        free(pcur->next);
        pcur->next = nn;
    }
}


size_t List_count(List * phead) {
    List * pcur = phead;
    size_t count = 0;
    while(pcur != NULL) {
        count++;
        pcur = pcur->next;
    }
    return count;
}

static void __List_sortArrayOfNodes(List ** array, size_t sz, int (*cmp)(List *, List *)) {
    for(size_t i = 0; i < sz - 1; i++)
        for(size_t j = i + 1; j < sz; j++)
            if(cmp(array[i], array[j]) == -1) {
                List * tmp = array[i];
                array[i] = array[j];
                array[j] = tmp;
            }
}

static List ** __List_toArray(List * phead, List ** array) {
    List * cur = phead;
    size_t i = 0;
    while(cur != NULL) {
        array[i] = cur;
        cur = cur->next;
        i++;
    }
    return array;
}

static List * __Array_toList(List ** array, size_t sz) {
    for(size_t i = 0; i < sz - 1; i++)
        array[i]->next = array[i+1];
    array[sz-1]->next = NULL;
    return *array;
}

void List_sort(List ** phead, int (*cmp)(List *, List*)) {
    size_t sz = List_count(*phead);
    List ** array = malloc(sizeof(List *) * sz);
    __List_toArray(*phead, array);
    __List_sortArrayOfNodes(array, sz, cmp);
    *phead = __Array_toList(array, sz);
    free(array);
}

void List_copy(List * src, List ** dest, void * (*create_copy)(void *), void (*onFree)(List *)) {
    List_free(*dest, onFree);
    List * pcur = src;
    while(pcur) {
        List_add(dest, create_copy(pcur->data));
        pcur = pcur->next;
    }
}

json_t * List_toJson(List * phead, json_t * (*dataToJson)(void *)) {
    json_t * arr = json_array();
    List * pcur = phead;
    while(pcur != NULL) {
        json_array_append_new(arr, dataToJson(pcur->data));
        pcur = pcur->next;
    }
    return arr;
}