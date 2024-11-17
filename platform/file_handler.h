
#ifndef __HYDROGEN_FILE_HANDLER_H
#define __HYDROGEN_FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <unistd.h>
#include "hydrogen.h"

typedef struct _FileReadRequest{
    char* file_path;
    char* result_buffer;

    uv_buf_t* buffer;

    uv_work_t* work;
    Promise* promise;
    JSContext *context;

} FileReadRequest;


typedef struct _FileWriteRequest {
    char* file_path;
    char* input_buffer;

    uv_buf_t* buffer;

    uv_work_t* work;
    Promise* promise;
    JSContext *context;

} FileWriteRequest;


FileReadRequest* init_file_read_request(char* file_path, JSContext *ctx) ;
void run_file_read_request(FileReadRequest* file_request);

FileWriteRequest* init_file_write_request(char* file_path, char* input_buffer, JSContext *ctx);
void run_file_write_request(FileWriteRequest* file_request);


#endif