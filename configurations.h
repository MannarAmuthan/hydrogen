

#ifndef __HYDROGEN_CONFIGURATIONS_H
#define __HYDROGEN_CONFIGURATIONS_H


typedef struct _configuration{
    char* script_path;
    char* script_string;
    
    int memory_dump_mode;
    int debug_mode;
} Configuration;

Configuration* init_configuration(int argc, char **argv);

#endif
