
#include "http_handler.h"



static void promise_http_request(uv_work_t *req, int status) {

    HttpRequest* http_request = (HttpRequest*)req->data;
    if(http_request->is_failed == 1){
        JSValue arg = JS_NewString(http_request->context, http_request->error);
        JSValue *argv = malloc(sizeof(JSValue));
        argv[0] = arg;
        reject_promise(http_request->context, http_request->promise, 1, argv);
    }
    else{
        JSValue arg = JS_NewString(http_request->context, http_request->response_body);
        JSValue *argv = malloc(sizeof(JSValue));
        argv[0] = arg;
        resolve_promise(http_request->context, http_request->promise, 1, argv);
    }
}

struct MemoryStruct {
  char *memory;
  size_t size;
};


static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}



static void http_request_work_cb(uv_work_t *req) {
    HttpRequest* http_request = (HttpRequest*)req->data;

    CURL *curl;
    CURLcode res;
 
    curl = curl_easy_init();

    struct MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    if(strcmp(http_request->method, "GET")==0){


        curl_easy_setopt(curl, CURLOPT_URL, http_request->url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl);

        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
            const char* error = curl_easy_strerror(res);
            http_request->error = (char*)malloc(strlen(error)+1);
            strcpy(http_request->error, error);
            http_request->is_failed = 1;
        }
        else{
            http_request->response_body = (char*)malloc(strlen(chunk.memory)+1);
            strcpy(http_request->response_body, chunk.memory);
            
        }
    }


    curl_easy_cleanup(curl);
}


void run_http_request(HttpRequest* http_request) {

    int t = uv_queue_work(uv_default_loop(), http_request->work, http_request_work_cb, promise_http_request);
    if (t != 0) {
        printf("Error");
    }
}


HttpRequest* init_http_request(char* url, char* method, JSContext *ctx) {

    HttpRequest* http_request = (HttpRequest*) malloc(sizeof(HttpRequest));

    http_request->url = (char *)malloc(strlen(url)+1);
    strcpy(http_request->url, url);

    http_request->method = (char *)malloc(strlen(method)+1);
    strcpy(http_request->method, method);

    http_request->work = (uv_work_t*)malloc(sizeof(uv_work_t));
    http_request->context = ctx;
    http_request->promise = malloc(sizeof(Promise));
    http_request->promise->rfuncs = malloc(sizeof(JSValue)*2);

    http_request->work->data = http_request;

    return http_request;

}