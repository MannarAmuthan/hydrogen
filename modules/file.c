
#include "alli.h"

#define countof(x) (sizeof(x) / sizeof((x)[0]))

static char* read_file(char* file_path)
{
    FileReadRequest* request = init_file_read_request(file_path);
    run_file_read_request(request);
    return request->result_buffer;
}

static JSValue js_read_file(JSContext *ctx, JSValueConst this_val,
                      int argc, JSValueConst *argv)
{

    if (JS_ToCString(ctx, argv[0]) == NULL)
        return JS_EXCEPTION;
    
    const char* file_path = JS_ToCString(ctx, argv[0]);

    const char* res = read_file(file_path);

    return JS_NewString(ctx, res);
}

static const JSCFunctionListEntry js_file_funcs[] = {
    JS_CFUNC_DEF("readFile", 1, js_read_file )
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