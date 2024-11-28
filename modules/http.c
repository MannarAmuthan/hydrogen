
#include "hydrogen.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))


static JSClassID js_http_server_class_id;


static JSValue js_http_server_factory(JSContext *ctx,
                             JSValueConst new_target,
                             int argc, JSValueConst *argv)
{
    HttpServerContext *server;
    JSValue obj = JS_UNDEFINED;
    JSValue proto;

    server = init_http_server("//","get", ctx);
    if (!server)
        return JS_EXCEPTION;

    obj = JS_NewObjectClass(ctx, js_http_server_class_id);

    JS_FreeValue(ctx, proto);
    if (JS_IsException(obj))
        goto fail;
    JS_SetOpaque(obj, server);
    return obj;
 fail:
    js_free(ctx, server);
    JS_FreeValue(ctx, obj);
    return JS_EXCEPTION;
}


static JSValue js_read_get_async(JSContext *ctx, JSValueConst this_val,
                      int argc, JSValueConst *argv)
{
    
    const char * arg_url = JS_ToCString(ctx, argv[0]);

    if (arg_url == NULL){
        return JS_EXCEPTION;
    }

    HttpRequest* request = init_http_request(arg_url, "GET" ,ctx);
    run_http_request(request);

    JSValue promise =  init_promise(ctx, request->promise);

    JS_FreeCString(ctx, arg_url);

    return promise;
}

static const JSCFunctionListEntry js_file_funcs[] = {
    JS_CFUNC_DEF("get", 1, js_read_get_async)
};

static void js_http_server_serve(JSContext *ctx, JSValueConst this_val,
                             int argc, JSValueConst *argv)
{
    HttpServerContext *s= JS_GetOpaque2(ctx, this_val, js_http_server_class_id);
    if (!s)
        return;

    run_http_server(s);
}


static const JSCFunctionListEntry js_point_proto_funcs[] = {
    JS_CFUNC_DEF("serve", 0, js_http_server_serve),
};


static int js_http_init(JSContext *ctx, JSModuleDef *m)
{
    JSValue point_factory;
    point_factory = JS_NewCFunction(ctx, js_http_server_factory, "createServer", 0);
    JS_SetModuleExport(ctx, m, "createServer", point_factory);

    JS_SetPropertyFunctionList(ctx, point_factory, js_point_proto_funcs, countof(js_point_proto_funcs));

    JS_SetClassProto(ctx, js_http_server_class_id, point_factory);


    return JS_SetModuleExportList(ctx, m, js_file_funcs,
                                  countof(js_file_funcs));
}


JSModuleDef *js_init_module_http(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_http_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_file_funcs, countof(js_file_funcs));
    JS_AddModuleExport(ctx, m, "createServer");
    return m;
}