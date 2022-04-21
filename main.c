#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

#define HELP 1
#define TOO_LONG 2
#define MAX_FILE_NAME_LENGTH 64
#define CONTENT_LENGTH 255

char* to_upper(char* str) {
    char* upper_str = malloc(sizeof(char) * MAX_FILE_NAME_LENGTH);

    for(int i = 0; str[i] != '\0'; ++i) {
        if(str[i] >= 'a' && str[i] <= 'z') {
            upper_str[i] = str[i] - 32;
        } else {
            upper_str[i] = str[i];
        }
    }

    return upper_str;
}

void print_help(int type) {
    switch(type) {
        case TOO_LONG:
            printf("Only one name is allowed, no spaces.\n");
            break;
    }
    printf("Please provide a name\n");
    printf("Usage: gen-c-h [name]\n");
}

void h_file(char* name, char* h_file_content) {
    char* upper_name = to_upper(name);

    snprintf(h_file_content, CONTENT_LENGTH, "#ifndef __%s_H\n#define __%s_H\n\n#endif\n", upper_name, upper_name);
}

void c_file(char* name, char* c_file_content) {
    snprintf(c_file_content, CONTENT_LENGTH, "#include \"%s.h\"\n", name);
}

int main(int argc, char** argv) {
    if(argc <= 1) {
        print_help(HELP);
        return 0;
    } else if (argc > 2) {
        print_help(TOO_LONG);
        return 0;
    }

    char* name = argv[1];

    char h_file_content[CONTENT_LENGTH];
    char h_file_name[MAX_FILE_NAME_LENGTH];
    char c_file_content[CONTENT_LENGTH];
    char c_file_name[MAX_FILE_NAME_LENGTH];

    h_file(name, h_file_content);
    snprintf(h_file_name, MAX_FILE_NAME_LENGTH, "%s.h", name);
    
    c_file(name, c_file_content);
    snprintf(c_file_name, MAX_FILE_NAME_LENGTH, "%s.c", name);

    FILE* c_f;
    FILE* h_f;

    char c_file_path[PATH_MAX];
    char h_file_path[PATH_MAX];

    char cwd[PATH_MAX - MAX_FILE_NAME_LENGTH];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        sprintf(c_file_path, "%s/%s", cwd, c_file_name);
        sprintf(h_file_path, "%s/%s", cwd, h_file_name);
    } else {
        perror("getcwd() error");
        return 1;
    }

    c_f = fopen(c_file_path, "w");
    h_f = fopen(h_file_path, "w");

    fputs(c_file_content, c_f);
    fputs(h_file_content, h_f);

    fclose(c_f);
    fclose(h_f);

    printf("Successfully created\n%s\n%s\n", c_file_path, h_file_path);

    return 0;
}