//
// Created by Yaroslav Bay on 10.05.17.
//

#include "hero.h"

json_t * Hero_toJson(Hero * self) {
    json_t * object = json_object();
    json_object_set(object, "id", json_integer(self->id));
    json_object_set(object, "name", json_string(self->name));
    json_object_set(object, "film", json_string(self->film));
    return object;
}


Hero * Hero_copy(Hero * self) {
    Hero * cp = malloc(sizeof(Hero));
    cp->id = self->id;
    strcpy(cp->name, self->name);
    strcpy(cp->film, self->film);
    return cp;
}

List * generateHeroes(unsigned quantity) {
    const int NAMES_LEN = 10;
    const int FILMS_LEN = 10;

    char names[NAMES_LEN][100] = {
            "Luke Skywalker",
            "Indiana Jones",
            "Batman",
            "James Bond",
            "John McClane",
            "Yoda",
            "Van Helsing",
            "Clarice Starling",
            "Harry Potter",
            "The Terminator"
    };

    char films[FILMS_LEN][100] = {
            "Star Wars",
            "Indiana Jones",
            "Batman",
            "Dr. No",
            "Die Hard series",
            "Star Wars",
            "Dracula",
            "The Silence of the Lambs",
            "Harry Potter",
            "The Terminator"
    };

    List * phead = List_new();
    for(unsigned i = 0; i < quantity; i++) {
        Hero * h = malloc(sizeof(Hero));
        h->id = i;
        strcpy(h->name, names[i % NAMES_LEN]);
        strcpy(h->film, films[i % FILMS_LEN]);
        List_add(&phead, h);
    }
    return phead;
}

List * filterHeroes(List * phead, const char * key, const char * value) {

    List * pfiltered = List_new();
    List * pcur = phead;

    while(pcur != NULL) {
        Hero * h = (Hero *)(pcur->data);

        char lkey[100];
        str_to_lower(key, lkey);
        char lvalue[100];
        str_to_lower(value, lvalue);
        char hlvalue[100];


        if(!strcmp(lkey, "id")) {
            if (h->id == atoi(value))
                List_add(&pfiltered, Hero_copy(h));

        } else if(!strcmp(lkey, "name")) {
            str_to_lower(h->name, hlvalue);

            if (!strcmp(hlvalue, lvalue))
                List_add(&pfiltered, Hero_copy(h));

        } else if(!strcmp(lkey, "film")) {
            str_to_lower(h->film, hlvalue);

            if (!strcmp(hlvalue, lvalue))
                List_add(&pfiltered, Hero_copy(h));
        }

        pcur = pcur->next;
    }

    return pfiltered;
}
