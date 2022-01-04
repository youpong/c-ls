#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct {
    char *path;
    char **entries;
} Dir;

Dir* dirs;
char** files;
    
void print_dir(Dir *dir) {
}

void retrive(char *path) {
}

/**
 * C言語によるls実装
 * などとすれば、ググらずにゼロから実装できる！
 */
int main(int argc, char* argv[])
{
    //    int result_code = 0;
    
    if (argc == 1) {
        retrive(".");
    } else {
        for (char **ptr = argv; *ptr != NULL; ++ptr)
            retrive(*ptr);
    }

    //    for (char **file = files; *file != NULL; ++file) {
    //        printf("%s\n", *file);
    //    }

    //    for () {
    //    }
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
