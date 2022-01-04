#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "util.h"
#include "file.h"

typedef enum {
    FT_REG,
    FT_DIR,
    FT_NOT_FOUND
} file_type;

typedef struct {
    char *path;
    char **entries;
} Dir;

Dir* dirs;
Vector *files;

file_type get_type(char *path) {
    file_type result = FT_NOT_FOUND;
    DIR* dir = opendir(*basedir(path) != '\0' ? basedir(path) : ".");

    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, filename(path)) != 0) {
            switch (ent->d_type) {
            case DT_DIR:
                result = FT_DIR;
                break;
            case DT_REG:
                result = FT_REG;
                break;
            }
            break;
        }
    }

    closedir(dir);
    return result;
}

void retrive(char *path) {
    switch (get_type(path)) {
    case FT_REG:
        vec_push(files, path);
        break;
    case FT_DIR:
        break;
    default:
        break;
    };
}

void print_dir(Dir *dir) {
}

void run_util_test();
void run_file_test();

/**
 * C言語によるls実装
 * などとすれば、ググらずにゼロから実装できる！
 */
int main(int argc, char* argv[])
{
    int result_code = 0;

    if (argc >= 2 && strcmp(argv[1], "-test") == 0) {
        run_util_test();
        run_file_test();
        printf("========================\n");
        printf(" All unit tests passed.\n");
        printf("========================\n");
        return 0;
    }

    files = new_vector();

    if (argc == 1) {
        retrive(".");
    } else {
        for (char **ptr = argv+1; *ptr != NULL; ++ptr)
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
