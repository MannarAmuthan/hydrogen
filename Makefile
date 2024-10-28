QUICKJS_PATH = /Users/amuthanm/Documents/personal/quickjs
QUICKJS_INCLUDE_PATH = $(QUICKJS_PATH)
QUICKJS_LIB_PATH = /Users/amuthanm/Documents/personal/quickjs
QUICKJS_AR = $(QUICKJS_LIB_PATH)/libquickjs.a

CC = clang
LD = clang
CCOPT = -g -O0
CCFLAGS = -c $(CCOPT)
LDFLAGS = -lpthread -lm -ldl -L$(QUICKJS_LIB_PATH) -lquickjs

main: main.o configurations.o
	$(LD) $^ $(LDFLAGS) -o $@ 

main.o: main.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

configurations.o: configurations.c
	$(CC) -I$(QUICKJS_INCLUDE_PATH) -Iincludes/ -I. $(CCFLAGS) $^ -o $@

