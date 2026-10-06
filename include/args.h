#ifndef ARGS_H
#define ARGS_H

typedef struct {
    char **files;
    char *args;

    int file_count;
    int args_count;
} Arguments;

void parse_arguments(int arguments_count, char** arguments, Arguments* obj);
void read_argument(char* argument, Arguments* arguments);

#endif