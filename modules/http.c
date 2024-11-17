
#include "alli.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))


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

static int js_http_init(JSContext *ctx, JSModuleDef *m)
{
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
    return m;
}