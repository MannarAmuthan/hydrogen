
#include "hydrogen.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))


static JSValue js_read_file_async(JSContext *ctx, JSValueConst this_val,
                      int argc, JSValueConst *argv)
{
    
    const char * arg_file_path = JS_ToCString(ctx, argv[0]);

    if (arg_file_path == NULL){
        return JS_EXCEPTION;
    }

    FileReadRequest* request = init_file_read_request(arg_file_path, ctx);
    run_file_read_request(request);

    JSValue promise =  init_promise(ctx, request->promise);

    JS_FreeCString(ctx, arg_file_path);

    return promise;
}

static JSValue js_write_file_async(JSContext *ctx, JSValueConst this_val,
                      int argc, JSValueConst *argv)
{
    const char* arg_file_path = JS_ToCString(ctx, argv[0]);
    const char* arg_file_content = JS_ToCString(ctx, argv[1]);

    if (arg_file_path == NULL){
        return JS_EXCEPTION;
    }

    if (arg_file_content == NULL){
        return JS_EXCEPTION;
    }
    
    FileWriteRequest* request = init_file_write_request(arg_file_path, arg_file_content, ctx);
    run_file_write_request(request);

    JSValue promise =  init_promise(ctx, request->promise);

    JS_FreeCString(ctx, arg_file_path);
    JS_FreeCString(ctx, arg_file_content);

    return promise;
}

static const JSCFunctionListEntry js_file_funcs[] = {
    JS_CFUNC_DEF("readFile", 1, js_read_file_async ),
    JS_CFUNC_DEF("writeFile", 1, js_write_file_async )
};

static int js_fib_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_file_funcs,
                                  countof(js_file_funcs));
}


JSModuleDef *js_init_module_file(JSContext *ctx, const char *module_name)
{
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_fib_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_file_funcs, countof(js_file_funcs));
    return m;
}