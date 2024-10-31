
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


typedef struct _FileWriteRequest{
    char* file_path;
    char* input_buffer;

    uv_fs_t* open_req; 
    uv_fs_t* read_req;   
    uv_fs_t* write_req;   
    uv_fs_t* close_req;
    uv_buf_t* buffer;

} FileWriteRequest;


FileReadRequest* init_file_read_request(char* file_path);
void run_file_read_request(FileReadRequest* file_request);

FileWriteRequest* init_file_write_request(char* file_path, char* input_buffer);
void run_file_write_request(FileWriteRequest* file_request);


#endif