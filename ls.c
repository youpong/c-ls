#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

int print_dir(char *);

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
    int ret_code = 0;

    switch (argc) {
    case 1:
        ret_code = print_dir(".");
        break;
    case 2:
        ret_code = print_dir(*(argv+1));
        break;
    default:
        for(++argv; *argv; ++argv) {
            printf("%s:\n", *argv);
            int ret;
            if (ret = print_dir(*argv)) {
                ret_code = ret;
            }
        }
    }

    return ret_code;
}

int print_dir(char *dirname) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
      if (errno != ENOTDIR) {
        fprintf(stderr, "unable to opendir %s\n", dirname);
        return 2;
      }
      printf("%s  \n", dirname);
      return 0;
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
    return 0;
}
