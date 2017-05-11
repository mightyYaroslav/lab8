//
// Created by Yaroslav Bay on 10.05.17.
//

#include "util.h"


int is_number(const char * str) {
    if(str == NULL) return 0;
    for(int i = 0 ;i < strlen(str); i++)
        if(!isdigit(str[i])) return 0;
    return 1;
}

void strftcpy(const char * src, char * dest, int from, int to) {
    for (int i = from; i < to; ++i)
        dest[i - from] = src[i];
    dest[to - from] = 0;
}

char * removeJunk(const char * src, char * dest) {

    for (int i = 0, j = 0; i < strlen(src); ++i, ++j) {

        if(i == strstr(src, "%20") - src) {
            i += 3;
            dest[j++] = ' ';
        }

        if(src[i] == '%')
            while(isdigit(src[++i]));

        dest[j] = src[i];

    }
    return dest;
}

char * str_to_lower(const char * str, char * out) {
    if(str != NULL) {
        for (int i = 0; i < strlen(str); i++)
            out[i] = (char) tolower(str[i]);
        out[strlen(str)] = '\0';
    }
    return out;
}

char * substr(const char * s, int index, int len,  char * out) {
    if (s != NULL && index >= 0 && len >= 0 && index + len <= strlen(s)) {
        for (int i = 0; i < len; i++)
            out[i] = s[i + index];
        out[len] = '\0';
    }
    return out;
}

//WARNING: Array allocated on heap
char ** split(const char * s, char splitter, int * count) {
    *count = 0;
    for(int i = 0; i < strlen(s); i++)
        if(s[i] == splitter) (*count)++;
    (*count)++;

    char ** a = malloc(sizeof(char *) * (*count));
    for(int i = 0; i < *count; i++)
        a[i] = malloc(sizeof(char) * 100);

    int j = 0;
    int ind = 0;
    for(int i = 0; i <= strlen(s); i++) {
        if(s[i] == splitter || s[i] == '\0') {
            substr(s, ind, i - ind, a[j]);
            if(a[j][0] == '\0')
                (*count)--;
            else
                j++;
            ind = i + 1;
        }
    }
    return a;
}

void free_splitted(char ** arr, int sz) {
    for(int i = 0; i < sz; i++)
        free(arr[i]);
    free(arr);
}
