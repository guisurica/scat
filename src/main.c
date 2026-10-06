#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "args.h"
#include "file_reader.h"

int main(int argc, char** argv) {
    if (argc <= 1) {
        printf("No arguments founded\n");
        printf("Use: scat <argument> <files>\n");
        exit(1);
    }

    Arguments arguments = {0};
    parse_arguments(argc, argv, &arguments);

    read_argument(arguments.args, &arguments);

    free(arguments.files);
    
    return 0;
}