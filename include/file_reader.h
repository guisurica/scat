#ifndef FILE_READER_H
#define FILE_READER_H   

#define MAX_LEN 128

int read_file(char *file_path, char **buffer);
void read_block(char *file_path, int begin_range, int end_range);

#endif