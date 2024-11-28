
#ifndef __HYDROGEN_HTTP_SERVER_H
#define __HYDROGEN_HTTP_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <unistd.h>
#include "hydrogen.h"
#include "mongoose.h"

typedef struct _HttpServerContext {
    struct mg_mgr* mgr;
} HttpServerContext;


typedef struct _HttpServe {
    char* path;
    char* method;
    JSValue* binded_function;

    HttpServerContext* server_context;

    JSContext *context;
} HttpServe;


HttpServerContext* init_http_server(char* url, char* method, JSContext *ctx);
void run_http_server(HttpServerContext* server_context);


#endif