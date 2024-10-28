#include "alli.h"


char* read_file(char* filename){
    char * buffer = 0;
    long length;
    FILE* f = fopen (filename, "rb");

    if (f)
    {
    fseek (f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
        fread (buffer, 1, length, f);
    }
    fclose (f);
    }

    return buffer;  
}


Configuration* init_configuration(int argc, char **argv){
    Configuration* configuration = (Configuration*) malloc(sizeof(Configuration));
    configuration->memory_dump_mode = 0;
    configuration->debug_mode = 0;
    if( argc == 1 ) {
        fprintf(stderr, "Expecting a file path");
        exit(3);
    }
    for(int i=0; i<argc; i++){
        if( i == 1){
            char* file_path = argv[i];
            configuration->script_path = file_path;
            configuration->script_string = read_file(file_path);
        }
        if(strcmp(argv[i], "-m") == 0){
            configuration->memory_dump_mode = 1;
        }
        if(strcmp(argv[i], "-t") == 0){
            configuration->debug_mode = 1;
        }
    }
    return configuration;
}