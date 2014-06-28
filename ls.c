#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

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
    DIR *dir;
    struct dirent *ent;
    char dirname[256];

    if (argc == 1) {
	strcpy(dirname, ".");
    } else {
	strcpy(dirname, argv[1]);
    }

    dir = opendir(dirname);
    if (dir == NULL) {
	fprintf(stderr, "unable to opendir\n");
    }

    while ((ent = readdir(dir)) != NULL) {
	if (ent->d_name[0] == '.') {
	    continue;
	}

	printf("%s  ", ent->d_name, ent->d_ino);
    }

    printf("\n");
    closedir(dir);
    return 0;
}
