//
// Created by Yaroslav Bay on 10.05.17.
//

/**
 * @file
 * @brief contains structure with server information
 */
#include <stdlib.h>
#include <time.h>
#include "jansson.h"

#ifndef LAB8_SERVER_INFO_H
#define LAB8_SERVER_INFO_H

/**
 * @typedef ServerInfo shortcut for struct ServerInfo
 */
typedef struct ServerInfo ServerInfo;

/**
 * @struct ServerInfo
 * @brief contains basic server information
 */
struct ServerInfo {
    char title[50];
    char developer[50];
    char time[50];
};

/**
 * @param self - pointer to ServerInfo structure
 * @return Json object with server info
 */
json_t * ServerInfo_toJson(ServerInfo * self);

#endif //LAB8_SERVER_INFO_H
