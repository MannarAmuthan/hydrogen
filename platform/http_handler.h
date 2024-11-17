
#ifndef __ALLI_HTTP_REQUEST_H
#define __ALLI_HTTP_REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <unistd.h>
#include "alli.h"

typedef struct _HttpRequest {
    char* url;
    char* method;

    char* response_body;             
    size_t response_body_length;
    long response_status_code;
    char* content_type;
    struct curl_slist* headers;
    double elapsed_time;
    int is_failed;
    char* error;

    uv_work_t* work;
    Promise* promise;
    JSContext *context;

} HttpRequest;


HttpRequest* init_http_request(char* url, char* method, JSContext *ctx);
void run_http_request(HttpRequest* http_request);


#endif