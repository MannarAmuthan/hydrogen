#ifndef __ALLI_H
#define __ALLI_H


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
#elif defined(__linux__) || defined(__GLIBC__)
#include <malloc.h>
#elif defined(__FreeBSD__)
#include <malloc_np.h>
#endif

#include <curl/curl.h>

#include "cutils.h"
#include "quickjs-libc.h"

#include "configurations.h"

#include "modules/file.h"
#include "modules/http.h"

#include "platform/promise.h"
#include "platform/file_handler.h"
#include "platform/http_handler.h"

#endif