#ifndef __ALLI_PROMISE_H
#define __ALLI_PROMISE_H


typedef struct _Promise{
    JSValue p;
    JSValue* rfuncs;
} Promise;

JSValue init_promise(JSContext *ctx, Promise *p);
void settle_promise(JSContext *ctx, Promise *p, int is_reject, int argc, JSValue *argv) ;

#endif