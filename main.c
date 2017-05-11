#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <event.h>

#include <evhttp.h>
#include "server_info.h"
#include "hero.h"
#include "file.h"


json_t * elToJson(void * e) {
    return Hero_toJson((Hero *)e);
}

void freeSimpleList(List * el) {
    free(el->data);
}

void generic_handler(struct evhttp_request *req, void *arg) {
    struct evbuffer *buf;
    buf = evbuffer_new();
    if (buf == NULL)
        err(1, "failed to create response buffer");

    struct evhttp_uri * uri = evhttp_uri_parse(evhttp_request_uri(req));

    const char * path = evhttp_uri_get_path(uri);
    int comp_count;
    char ** components = split(path, '/', &comp_count);

    char query[1000] = "";
    if(evhttp_uri_get_query(uri) != NULL)
        strcpy(query, evhttp_uri_get_query(uri));

    char * json_str = NULL;
    int success = 1;

    if(!strncmp(path, "/favorites", strlen("/favorites"))) {
        List * heroes = generateHeroes(10);

        if(strcmp(query, "")) {
            int count;
            char ** strings = split(query, '=', &count);

            removeJunk(strings[1], strings[1]);

            List * filtered = filterHeroes(heroes, strings[0], strings[1]);
            json_str = json_dumps(List_toJson(filtered, elToJson), JSON_INDENT(2));
            List_free(filtered, freeSimpleList);
            free_splitted(strings, count);

        } else if (comp_count > 1 && is_number(components[1])) {
            List * filtered = filterHeroes(heroes, "id", components[1]);
            if(filtered == NULL)
                success = 0;
            else
                json_str = json_dumps(List_toJson(filtered, elToJson), JSON_INDENT(2));
            List_free(filtered, freeSimpleList);

        } else {
            json_t * arr = List_toJson(heroes, elToJson);
            json_str = json_dumps(arr, JSON_INDENT(2));
        }

        List_free(heroes, freeSimpleList);

    } else if(!strncmp(path, "/file", strlen("/file"))) {

        if(comp_count > 1 && !strcmp(components[1], "data")) {
            File f = File_read("data/data.txt");
            List * numbers = numbersUnpairPos(&f);
            json_str = json_dumps(List_toJson(numbers, numbersToJson), JSON_INDENT(2));
            List_free(numbers, freeSimpleList);

        } else {
            File f = File_read("data/data.txt");
            json_str = json_dumps(File_toJson(&f), JSON_INDENT(2));
        }

    } else if(path[0] == '/' && strlen(path) == 1) {
        time_t rawTime;
        struct tm * timeInfo;

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        ServerInfo info = {
            "FavHeroesServer",
            "YAROSLAV_BAY",
        };

        strcpy(info.time , asctime(timeInfo));
        info.time[strlen(info.time) - 1] = '\0';

        json_str = json_dumps(ServerInfo_toJson(&info), JSON_INDENT(2));

    } else {
        success = 0;
    }

    if(json_str != NULL) {
        evbuffer_add_printf(buf, "%s", json_str);
        free(json_str);
    }

    if(success)
        evhttp_send_reply(req, HTTP_OK, "OK", buf);
    else
        evhttp_send_error(req, HTTP_NOTFOUND, "Not found");
    free_splitted(components, comp_count);

}

int main(int argc, char ** argv) {

    if(argc < 2) {
        puts("Please, specify port in command line args");
    } else {
        struct evhttp *httpd;
        event_init();

        httpd = evhttp_start("0.0.0.0", atoi(argv[1]));

        if(httpd) {
            puts("Server started");
            evhttp_set_gencb(httpd, generic_handler, NULL);
            event_dispatch();
            evhttp_free(httpd);

        } else {
            puts("The port is taken =(");
        }
    }
    return 0;
}