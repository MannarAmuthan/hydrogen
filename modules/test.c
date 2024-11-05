#include "alli.h"

// Structure to hold the data for the async work
typedef struct {
    JSContext *ctx;
    JSValue promise;
    JSValue resolve_func;
    JSValue reject_func;
    uv_work_t req;
} AsyncData;


void async_work(uv_work_t *req) {

}


void async_after_work(uv_work_t *req, int status) {
    AsyncData *data = req->data;
    JSContext *ctx = data->ctx;


    JSValue result = JS_NewString(ctx, "Promise resolved successfully");
    JSValue ret = JS_Call(ctx, data->resolve_func, JS_UNDEFINED, 1, &result);

    // Clean up
    JS_FreeValue(ctx, result);
    JS_FreeValue(ctx, ret);
    JS_FreeValue(ctx, data->resolve_func);
    JS_FreeValue(ctx, data->reject_func);
    JS_FreeValue(ctx, data->promise);
    free(data);
}

// The JS function that sets up the promise
static JSValue js_promise_function(JSContext *ctx, JSValueConst this_val, int argc, JSValueConst *argv) {
    
    JSValue rfuncs[2];

    JSValue promise = JS_NewPromiseCapability(ctx, rfuncs);

    if (JS_IsException(promise))
        return promise;

    // Allocate memory for the async data
    AsyncData *data = malloc(sizeof(AsyncData));
    data->ctx = ctx;
    data->promise = JS_DupValue(ctx, promise);
    data->resolve_func = JS_DupValue(ctx, rfuncs[0]);
    data->reject_func = JS_DupValue(ctx, rfuncs[1]);

    data->req.data = data;

    uv_queue_work(uv_default_loop(), &data->req, async_work, async_after_work);

    JS_FreeValue(ctx, rfuncs[0]);
    JS_FreeValue(ctx, rfuncs[1]);
    
    return promise;
}


static const JSCFunctionListEntry js_file_funcs_test[] = {
    JS_CFUNC_DEF("myAsyncFunction", 0, js_promise_function )
};

static int js_test_init(JSContext *ctx, JSModuleDef *m)
{
    return JS_SetModuleExportList(ctx, m, js_file_funcs_test,
                                  countof(js_file_funcs_test));
}

JSModuleDef* js_init_module_test(JSContext *ctx, const char *module_name) {
    JSModuleDef *m;
    m = JS_NewCModule(ctx, module_name, js_test_init);
    if (!m)
        return NULL;
    JS_AddModuleExportList(ctx, m, js_file_funcs_test, countof(js_file_funcs_test));
    return m;
}