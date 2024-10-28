

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#if defined(__APPLE__)
#include <malloc/malloc.h>
#elif defined(__linux__)
#include <malloc.h>
#endif

#include "alli.h"

#include <quickjs.h>

#include "cutils.h"
#include "quickjs-libc.h"

#include <math.h>


void trace(Configuration* configuration, char* log){
    if(configuration->debug_mode == 1){
        printf("%s",log);
    }
}

int main(int argc, char **argv)
{
        


        Configuration* configuration = init_configuration(argc, argv);
     

        trace(configuration, "Creating runtime\r\n");
        JSRuntime *rt = JS_NewRuntime();
        if (!rt)
        {
            fprintf(stderr, "Cannot allocate JS runtime\n");
            exit(2);
        }

        JS_SetMemoryLimit(rt, 80 * 1024);
        JS_SetMaxStackSize(rt, 10 * 1024);
        trace(configuration, "Creating context\r\n");
        JSContext *ctx = JS_NewContext(rt);
        if (!ctx)
        {
            fprintf(stderr, "Cannot allocate JS context\n");
            exit(2);
        }

        js_init_module_std(ctx, "std");
        js_init_module_os(ctx, "os");

        js_std_add_helpers(ctx, argc, argv);




        const char *expr = configuration->script_string;
        JSValue r = JS_Eval(ctx, expr, strlen(expr), "", 0);
        if (JS_IsException(r))
        {   
            js_std_dump_error(ctx);
            fprintf(stderr, "Error Evaluating Script\r\n");
            exit(4);
        }

             
        JS_FreeValue(ctx, r);

        if(configuration->memory_dump_mode == 1){
            JSMemoryUsage stats;
            JS_ComputeMemoryUsage(rt, &stats);
            JS_DumpMemoryUsage(stdout, &stats, rt);
        }

        JS_FreeContext(ctx);
        JS_FreeRuntime(rt);
}

void app_main()
{
    main(0, NULL);
}