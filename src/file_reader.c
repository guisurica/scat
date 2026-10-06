#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_LEN 128

int read_file(char *file_path, char **buffer) {
    
    if (file_path == NULL) return 0;

    FILE *f = fopen(file_path, "r");
    if (f == NULL) {
        perror("Error opening file");
        exit(1);
    }

    char *temp = malloc(MAX_LEN * sizeof(char));
    int temp_cap = MAX_LEN;
    int temp_size = 0;
    int size = 0;

    do {
        if (temp_size + temp_cap >= MAX_LEN) {
            temp_cap += MAX_LEN;
            temp = realloc(temp, temp_cap * sizeof(char));
            if (temp == NULL) {
                perror("realloc error");
                printf("Error code: %d\n", errno);

                free(temp);
                fclose(f);

                exit(1);
            }
        }

        size = fread(temp + temp_size, sizeof(char), MAX_LEN, f);
        temp_size += size;
    } while(size > 0);

    fclose(f);

    temp[temp_size] = '\0';

    *buffer = temp;
    
    return temp_size;
}

void read_block(char *file_path, int begin_range, int end_range) {
    char *temp_file = NULL;
    char *block_buffer = malloc(end_range * sizeof(char));

    int temp_file_size = read_file(file_path, &temp_file);
    temp_file[temp_file_size] = '\0';

    int cursor = 0;
    int dest_buffer_cursor = 0;
    while(temp_file[cursor] != '\0') {

        if (&temp_file[cursor] >= &temp_file[begin_range] && 
            &temp_file[cursor] <= &temp_file[end_range]) {

            memcpy(&block_buffer[dest_buffer_cursor], &temp_file[cursor], sizeof(char));

            dest_buffer_cursor += 1;
        }

        cursor += 1;
    }

    block_buffer[cursor] = '\0';

    printf("%s\n", block_buffer);
    
    free(temp_file);
    free(block_buffer);
}