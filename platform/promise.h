#ifndef __HYDROGEN_PROMISE_H
#define __HYDROGEN_PROMISE_H


typedef struct _Promise{
    JSValue p;
    JSValue* rfuncs;
} Promise;

JSValue init_promise(JSContext *ctx, Promise *p);
void settle_promise(JSContext *ctx, Promise *p, int is_reject, int argc, JSValue *argv) ;


void resolve_promise(JSContext *ctx, Promise *p, int argc, JSValue *argv);
void reject_promise(JSContext *ctx, Promise *p, int argc, JSValue *argv);

#endif