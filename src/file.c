//
// Created by Yaroslav Bay on 10.05.17.
//

#include "file.h"

File File_read(const char * path) {
    FILE * fin = fopen(path, "r");
    File f = {
        0,
        "",
        ""
    };

    if(fin != NULL) {
        strcpy(f.name, path);

        while (!feof(fin)) {
            char buf[1000];
            fgets(buf, 1000, fin);
            buf[strlen(buf) - 1] = '\0';
            strcat(f.content, buf);
        }

        f.size = strlen(f.content);
        fclose(fin);
    }
    return f;
}

json_t * File_toJson(File * self) {
    if(self == NULL) return NULL;
    json_t * object = json_object();
    json_object_set(object, "size", json_integer((int)(self->size)));
    json_object_set(object, "name", json_string(self->name));
    json_object_set(object, "content", json_string(self->content));
    return object;
}

List * numbersUnpairPos(File * self) {
    if(self == NULL) return NULL;

    List * pnumbers = List_new();

    for (int i = 0; i < strlen(self->content); ++i)
        if(isdigit(self->content[i]) && i % 2) {
            int * num = malloc(sizeof(int));
            *num = self->content[i] - '0';
            List_add(&pnumbers, num);
        }

    return pnumbers;
}

json_t * numbersToJson(void * num) {
    return json_integer(*(int *)num);
}
