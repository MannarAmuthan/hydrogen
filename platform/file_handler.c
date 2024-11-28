#include "file_handler.h"


void free_file_read_request(FileReadRequest* file_request);
void free_file_write_request(FileWriteRequest* file_request);


static void promise_file_after_read_request(uv_work_t *req, int status) {

    FileReadRequest* file_request = (FileReadRequest*)req->data;
    JSValue arg = JS_NewString(file_request->context, file_request->result_buffer);
    JSValue *argv = malloc(sizeof(JSValue));
    argv[0] = arg;
    settle_promise(file_request->context, file_request->promise, 0, 1, argv);
    free_file_read_request(file_request);
}

static void file_read_work_cb(uv_work_t *req) {
    FileReadRequest* file_request = (FileReadRequest*)req->data;

    uv_fs_t file_req;
    uv_file fd;
    int r;

    r = uv_fs_open(NULL, &file_req, file_request->file_path, O_RDONLY, 0, NULL);

    uv_fs_req_cleanup(&file_req);
    if (r < 0) {
        return;
    }
    
    fd = r;
    size_t offset = 0;
    
    do{
        r = uv_fs_read(NULL, &file_req, fd, file_request->buffer, 1, offset, NULL);
        uv_fs_req_cleanup(&file_req);
        if (r <= 0) {
            break;
        }
        offset += r;
        if (r != 0) {
            break;
        }
    }while(1);

    uv_fs_close(NULL, &file_req, fd, NULL);
    uv_fs_req_cleanup(&file_req);
}

void run_file_read_request(FileReadRequest* file_request) {
  
    int t = uv_queue_work(uv_default_loop(), file_request->work, file_read_work_cb, promise_file_after_read_request);
    if (t != 0) {
        printf("Error");
    }
}


FileReadRequest* init_file_read_request(char* file_path, JSContext *ctx) {

    FileReadRequest* file_request = (FileReadRequest*) malloc(sizeof(FileReadRequest));

    unsigned int len = 1000*sizeof(char);
    file_request->result_buffer = (char *)malloc(len);

    file_request->file_path = (char *)malloc(strlen(file_path) + 1);
    strcpy(file_request->file_path, file_path);

    file_request->work = (uv_work_t*)malloc(sizeof(uv_work_t));
    file_request->buffer = (uv_buf_t*)malloc(sizeof(uv_buf_t));
    file_request->context = ctx;
    file_request->promise = malloc(sizeof(Promise));
    file_request->promise->rfuncs = malloc(sizeof(JSValue)*2);
    
    *(file_request->buffer) = uv_buf_init(file_request->result_buffer, len);

    file_request->work->data = file_request;

    return file_request;

}

void free_file_read_request(FileReadRequest* file_request) {
    free(file_request->work);
    free(file_request->buffer);
    free(file_request->promise->rfuncs);
    free(file_request->promise);
    free(file_request->file_path);
    free(file_request->result_buffer);
    free(file_request);

}


static void promise_file_after_write_request(uv_work_t *req, int status) {

    FileWriteRequest* file_request = (FileWriteRequest*)req->data;
    JSValue arg = JS_NewInt32(file_request->context, 3);
    JSValue *argv = malloc(sizeof(JSValue));
    argv[0] = arg;
    resolve_promise(file_request->context, file_request->promise, 1, argv);
    free_file_write_request(file_request);
}

static void file_write_work_cb(uv_work_t *req) {
    FileReadRequest* file_request = (FileReadRequest*)req->data;

    uv_fs_t file_req;
    uv_file fd;
    int r;
    
    int flags = O_CREAT | O_WRONLY | O_TRUNC;
    int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH; 

    r = uv_fs_open(NULL, &file_req, file_request->file_path, flags , mode, NULL);
    uv_fs_req_cleanup(&file_req);

    if (r < 0) {
        printf("error opening file for writing\n");
        return;
    }
    
    fd = r;
    size_t offset = 0;

    r = uv_fs_write(uv_default_loop(), &file_req, fd,
                        file_request->buffer, 1, -1, NULL);
    if (r < 0) {
        printf("error writing file\n");
        return;
    }
    uv_fs_req_cleanup(&file_req);

    uv_fs_close(NULL, &file_req, fd, NULL);
    uv_fs_req_cleanup(&file_req);
}

void run_file_write_request(FileWriteRequest* file_request) {

    int t = uv_queue_work(uv_default_loop(), file_request->work, file_write_work_cb, promise_file_after_write_request);
    if (t != 0) {
        printf("Error");
    }
}


FileWriteRequest* init_file_write_request(char* file_path, char* input_buffer, JSContext *ctx) {

    FileWriteRequest* file_request = (FileWriteRequest*) malloc(sizeof(FileWriteRequest));

    file_request->file_path = (char *)malloc(strlen(file_path)+1);
    strcpy(file_request->file_path, file_path);

    file_request->input_buffer = (char *)malloc(strlen(input_buffer)+1);
    strcpy(file_request->input_buffer, input_buffer);

    file_request->buffer = (uv_buf_t*)malloc(sizeof(uv_buf_t));
    
    *(file_request->buffer) = uv_buf_init(file_request->input_buffer, (strlen(file_request->input_buffer)*sizeof(char)));

    file_request->work = (uv_work_t*)malloc(sizeof(uv_work_t));
    file_request->context = ctx;
    file_request->promise = malloc(sizeof(Promise));
    file_request->promise->rfuncs = malloc(sizeof(JSValue)*2);

    file_request->work->data = file_request;

    return file_request;

}

void free_file_write_request(FileWriteRequest* file_request) {
    free(file_request->work);
    free(file_request->buffer);
    free(file_request->promise->rfuncs);
    free(file_request->promise);
    free(file_request->file_path);
    free(file_request->input_buffer);
    free(file_request);
}
