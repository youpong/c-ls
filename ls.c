#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "util.h"

enum file_type { FT_FILE, FT_DIR, FT_NOT_FOUND } ;

typedef struct {
    char *path;
    char **entries;
} Dir;

Dir* dirs;
Vector *files;

enum file_type get_type(char *path) {
    return FT_NOT_FOUND;
}

void retrive(char *path) {
    switch (get_type(path)) {
    case FT_FILE:
        break;
    case FT_DIR:
        break;
    default:
        break;
    };
}

void print_dir(Dir *dir) {
}

/**
 * C言語によるls実装
 * などとすれば、ググらずにゼロから実装できる！
 */
int main(int argc, char* argv[])
{
    int result_code = 0;

    files = new_vector();
        
    if (argc == 1) {
        retrive(".");
    } else {
        for (char **ptr = argv; *ptr != NULL; ++ptr)
            retrive(*ptr);
    }

    for(int i = 0; i < files->len; ++i) {
        printf("%s\n", (char *)files->data[i]);
    }

    for (Dir *dir = dirs; dir != NULL; ++dir) {
        print_dir(dir);
    }

    return result_code;
}

/*
int print_dir(char* dirname)
{
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        if (errno != ENOTDIR) {
            fprintf(stderr, "unable to opendir %s\n", dirname);
            return 2;
        }
        printf("%s  \n", dirname);
        return 0;
    }

    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] == '.') {
            continue;
        }

        printf("%s  ", ent->d_name);
    }
    printf("\n");

    closedir(dir);
    return 0;
}
*/
