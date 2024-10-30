#include "file_handler.h"

void on_open(uv_fs_t *req) {

  if (req->result != -1) {

    FileReadRequest* file_request = (FileReadRequest*)req->data ;
    uv_fs_read(uv_default_loop(), file_request->read_req, req->result,
        file_request->buffer, 1, -1, on_read);

  }
  else {
    fprintf(stderr, "Error opening file!");
  }

  uv_fs_req_cleanup(req);
}

void on_read(uv_fs_t *req) {


    if (req->result < 0) {

      fprintf(stderr, "Read error!");

    }
    else if (req->result == 0) {
      FileReadRequest* file_request = (FileReadRequest*)req->data ;
      uv_fs_close(uv_default_loop(), file_request->close_req, file_request->open_req->result, NULL);
    }
    else {
      FileReadRequest* file_request = (FileReadRequest*)req->data ;
      uv_fs_close(uv_default_loop(), file_request->close_req, file_request->open_req->result, NULL);  
    }

    uv_fs_req_cleanup(req);
}


void on_write(uv_fs_t *req) {

      if (req->result < 0) {

        fprintf(stderr, "Write error!");

      }
      else {

        FileReadRequest* file_request = (FileReadRequest*)req->data ;
        uv_fs_read(uv_default_loop(), file_request->read_req, file_request->open_req->result, 
            file_request->buffer, file_request->buffer->len, -1, on_read);

      }

      uv_fs_req_cleanup(req);
}


FileReadRequest* init_file_read_request(char* file_path) {

    FileReadRequest* file_request = (FileReadRequest*) malloc(sizeof(FileReadRequest));

    unsigned int len = 1000*sizeof(char);
    file_request->result_buffer = (char *)malloc(len);

    file_request->file_path = (char *)malloc(strlen(file_path));
    strcpy(file_request->file_path, file_path);

    file_request->open_req = (uv_fs_t*)malloc(sizeof(uv_fs_t));
    file_request->close_req = (uv_fs_t*)malloc(sizeof(uv_fs_t));
    file_request->read_req = (uv_fs_t*)malloc(sizeof(uv_fs_t));
    file_request->write_req = (uv_fs_t*)malloc(sizeof(uv_fs_t));
    file_request->buffer = (uv_buf_t*)malloc(sizeof(uv_buf_t));
    
    *(file_request->buffer) = uv_buf_init(file_request->result_buffer, len);

    file_request->open_req->data = file_request;
    file_request->close_req->data = file_request;
    file_request->read_req->data = file_request;
    file_request->write_req->data = file_request;

    return file_request;

}


FileReadRequest* run_file_read_request(FileReadRequest* file_request) {
    uv_fs_open(uv_default_loop(), file_request->open_req, file_request->file_path, O_RDONLY, 0, on_open);
    uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}
