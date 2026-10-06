#include "args.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "file_reader.h"

#define START_FILE_INDEX 2
#define MAX_FILES_LENGTH 128

void parse_arguments(int argc, char **argv, Arguments* obj) {
    obj->args = argv[1];
    obj->args_count = 1;
    obj->files = malloc(1024 * sizeof(char));

    int file_location_index = 0;
    for(int i = 0; i < argc; i++) {
        if (i >= START_FILE_INDEX) {
            char *current_file_path = argv[i];
            obj->files[file_location_index] = current_file_path;
            obj->file_count++;
            file_location_index++;
        }
    }
}

void read_argument(char* argument, Arguments* arguments) {
    if (strcmp(argument, "--help") == 0) {
        printf("--show-all <files>: read all text files\n");
        printf("--show-block <begin> <end>: read the range of chars, include begin and end\n");
        exit(0);
    } else if (strcmp(argument, "--show-all") == 0) {
        for(int i = 0; i < arguments->file_count; i++) {
            char *buffer = NULL;
            
            int file_size = read_file(arguments->files[i], &buffer);
            if (buffer == NULL) {
                return;
            };

            printf("%s\n", buffer);

            printf("<END OF FILE> Bytes readed %d\n", file_size);
            printf(" \n");

            free(buffer);
        }
    } else if (strcmp(argument, "--show-block") == 0) {
        char *file_path = arguments->files[0];
        unsigned int begin = strtol(arguments->files[1], NULL, 10);
        unsigned int end = strtol(arguments->files[2], NULL, 10);

        read_block(file_path, begin, end);
    } else {
        printf("No arguments founded\n");
        printf("Use: scat <argument> <files>\n");
        exit(1);    
    }
}

