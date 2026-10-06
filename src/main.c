#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "args.h"
#include "file_reader.h"
#include "message.h"

int main(int argc, char** argv) {
    if (argc <= 1) {
        show_helper_message();
        exit(1);
    }

    Arguments arguments = {0};
    parse_arguments(argc, argv, &arguments);

    read_argument(arguments.args, &arguments);

    free(arguments.files);
    
    return 0;
}