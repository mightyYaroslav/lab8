//
// Created by Yaroslav Bay on 10.05.17.
//

#include "server_info.h"

json_t * ServerInfo_toJson(ServerInfo * self) {
    json_t * object = json_object();
    json_object_set(object, "title", json_string(self->title));
    json_object_set(object, "developer", json_string(self->developer));
    json_object_set(object, "time", json_string(self->time));
    return object;
}