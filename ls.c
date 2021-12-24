#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void print_dir(char *);

/**
 * C言語によるls実装
 * man 3 opendir
 * man 3 readdir
 * などとすれば、ググらずにゼロから実装できる！
 *
 * 実行方法: gcc ls.c && ./a.out /tmp
 */
int main(int argc, char *argv[])
{
    if (argc == 1) {
        print_dir(".");
	return 0;
    }

    for(++argv; *argv; ++argv) {      
        print_dir(*argv);
    }

    return 0;
}

void print_dir(char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        fprintf(stderr, "unable to opendir %s\n", dirname);
        exit(1);
    }

    struct dirent *ent;
    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_name[0] == '.') {
                continue;
        }

        printf("%s  ", ent->d_name);
    }
    printf("\n");

    closedir(dir);
}
