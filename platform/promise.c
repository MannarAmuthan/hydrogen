
#include "hydrogen.h"


JSValue init_promise(JSContext *ctx, Promise *p) {
    JSValue rfuncs[2];
    p->p = JS_NewPromiseCapability(ctx, rfuncs);
    if (JS_IsException(p->p)) {
        return JS_EXCEPTION;
    }
    p->rfuncs[0] = JS_DupValue(ctx, rfuncs[0]);
    p->rfuncs[1] = JS_DupValue(ctx, rfuncs[1]);

    JS_FreeValue(ctx, rfuncs[0]);
    JS_FreeValue(ctx, rfuncs[1]);

    return JS_DupValue(ctx, p->p);
}


void settle_promise(JSContext *ctx, Promise *p, int is_reject, int argc, JSValue *argv) {

    JSValue ret = JS_Call(ctx, p->rfuncs[is_reject], p->p, argc, argv);
    for (int i = 0; i < argc; i++) {
        JS_FreeValue(ctx, argv[i]);
    }
    free(argv);
    JS_FreeValue(ctx, ret);
    JS_FreeValue(ctx, p->rfuncs[0]);
    JS_FreeValue(ctx, p->rfuncs[1]);
    JS_FreeValue(ctx, p->p);
    
}

void resolve_promise(JSContext *ctx, Promise *p, int argc, JSValue *argv) {
    settle_promise(ctx, p, 0, argc, argv);
}

void reject_promise(JSContext *ctx, Promise *p, int argc, JSValue *argv) {
    settle_promise(ctx, p, 1, argc, argv);
}