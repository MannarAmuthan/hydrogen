#include "http_server.h"

HttpServerContext* init_http_server(char* url, char* method, JSContext *ctx){
    HttpServerContext* server_context = malloc(sizeof(HttpServerContext));
    server_context->mgr = malloc(sizeof(struct mg_mgr));

    return server_context;
}


static void ev_handler(struct mg_connection *c, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_MSG) {
    struct mg_http_message *hm = (struct mg_http_message *) ev_data;
    if (mg_match(hm->uri, mg_str("/api/time/get"), NULL)) {
      mg_http_reply(c, 200, "", "{%m:%lu}\n", MG_ESC("time"), time(NULL));
    } else {
      mg_http_reply(c, 500, "", "{%m:%m}\n", MG_ESC("error"), MG_ESC("Unsupported URI")); 
    }
  }
}

void run_http_server(HttpServerContext* server_context){
  mg_mgr_init(server_context->mgr);  // Initialise event manager
  mg_http_listen(server_context->mgr, "http://0.0.0.0:8000", ev_handler, NULL);  // Setup listener

  for (;;) mg_mgr_poll(server_context->mgr, 1000);

}