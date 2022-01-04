#include "file.h"
#include "util.h"
#include <dirent.h>
#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef enum {
    FT_REG,
    FT_DIR,
    FT_NOT_FOUND
} file_type;

typedef struct {
    char* path;
    Vector* entries;
} Dir;

char* program_name;
int result_code = 0;
Vector* dirs;
Vector* files;

void run_util_test();
void run_file_test();

file_type get_type(char* path)
{
    file_type result = FT_NOT_FOUND;
    char* d = basedir(path);
    if (*d == '\0')
        d = ".";
    DIR* dir = opendir(d);

    struct dirent* ent;
    while ((ent = readdir(dir)) != NULL) {
        if (strcmp(ent->d_name, filename(path)) == 0) {
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

void retrive(char* path)
{
    Dir* dir;
    DIR* d;
    struct dirent* ent;

    switch (get_type(path)) {
    case FT_REG:
        vec_push(files, path);
        break;
    case FT_DIR:
        dir = malloc(sizeof(Dir));
        dir->path = path;
        dir->entries = new_vector();

        d = opendir(path);
        while ((ent = readdir(d)) != NULL) {
            vec_push(dir->entries, ent->d_name);
        }
        closedir(d);
        vec_push(dirs, dir);
        break;
    default:
        fprintf(stderr, "%s: cannot access '%s': No such file or directory\n",
            program_name, path);
        result_code = 2;
        break;
    };
}

static int cmp_strp(const void* p1, const void* p2)
{
    return strcmp(*(char* const*)p1, *(char* const*)p2);
}

void print_dir(Dir* dir, bool show_header)
{
    if (show_header)
        printf("%s:\n", dir->path);

    Vector* entries = dir->entries;
    qsort(entries->data, entries->len, sizeof(char*), cmp_strp);

    for (int i = 0; i < entries->len; ++i) {
        if (*((char*)entries->data[i]) != '.')
            printf("%s\n", entries->data[i]);
    }
}

/**
 * C言語によるls実装
 * などとすれば、ググらずにゼロから実装できる！
 */
int main(int argc, char* argv[])
{
    if (argc >= 2 && strcmp(argv[1], "-test") == 0) {
        run_util_test();
        run_file_test();
        printf("========================\n");
        printf(" All unit tests passed.\n");
        printf("========================\n");
        return 0;
    }

    program_name = argv[0];
    files = new_vector();
    dirs = new_vector();

    if (argc == 1)
        retrive(".");
    else
        for (char** ptr = argv + 1; *ptr != NULL; ++ptr)
            retrive(*ptr);

    //
    // print files and entries ...
    //

    for (int i = 0; i < files->len; ++i) {
        printf("%s\n", (char*)files->data[i]);
    }

    bool need_delm = files->len > 0 ? true : false;
    for (int i = 0; i < dirs->len; ++i) {
        if (need_delm)
            printf("\n");
        print_dir(dirs->data[i], argc > 2);
        need_delm = true;
    }

    return result_code;
}
