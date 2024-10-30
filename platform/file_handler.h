
#ifndef __ALLI_FILE_HANDLER_H
#define __ALLI_FILE_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
#include <unistd.h>


typedef struct _FileReadRequest{
    char* file_path;
    char* result_buffer;

    uv_fs_t* open_req; 
    uv_fs_t* read_req;   
    uv_fs_t* write_req;   
    uv_fs_t* close_req;
    uv_buf_t* buffer;

} FileReadRequest;


void on_open(uv_fs_t *req);
void on_read(uv_fs_t *req);
void on_write(uv_fs_t *req);


FileReadRequest* init_file_read_request();
FileReadRequest* run_file_read_request(FileReadRequest* file_request);




#endif