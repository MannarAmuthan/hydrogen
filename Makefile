QUICKJS_PATH = /Users/amuthanm/Documents/personal/quickjs
QUICKJS_INCLUDE_PATH = $(QUICKJS_PATH)
QUICKJS_LIB_PATH = /Users/amuthanm/Documents/personal/quickjs

LIBUV_PATH = /Users/amuthanm/Documents/personal/libuv
LIBUV_INCLUDE_PATH = $(LIBUV_PATH)/include
LIBUV_LIB_PATH = $(LIBUV_PATH)/.libs

CURL_PATH = curl
CURL_INCLUDE_PATH = $(CURL_PATH)/include
CURL_LIB_PATH = $(CURL_PATH)/lib/.libs

DYLD_LIBRARY_PATH=curl/lib/.libs

CC = clang
LD = clang
CCOPT = -g -O0
CCFLAGS = -c $(CCOPT)
LDFLAGS = -lpthread -lm -ldl -L$(QUICKJS_LIB_PATH) -L$(LIBUV_LIB_PATH) -L$(CURL_LIB_PATH) -lquickjs -luv -lcurl

main: main.o configurations.o file.o file_handler.o promise.o http_handler.o http.o
	$(LD) $^ $(LDFLAGS) -o $@ 

main.o: main.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

configurations.o: configurations.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

file.o: modules/file.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -I$(LIBUV_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@


http.o: modules/http.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -I$(LIBUV_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@


file_handler.o: platform/file_handler.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -I$(LIBUV_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

http_handler.o: platform/http_handler.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -I$(LIBUV_INCLUDE_PATH) -I$(CURL_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

promise.o: platform/promise.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -I$(LIBUV_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

clean:
	rm -f *.o

