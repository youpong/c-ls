#include <stdio.h>
#include <string.h>

char *basedir(char *path) {
    char *result = strdup(path);

    for(char *ptr = result + strlen(result) - 1; ptr >= result; --ptr) {
        if (*ptr == '/') {
            *(ptr + 1) = '\0';
            return result;
        }
    }
    result[0] = '\0';
    return result;
}

char *filename(char *path) {
    char *result;

    int i;
    for (i = strlen(path) - 1; i >= 0; --i) {
        if (path[i] == '/') {
            break;
        }
    }

    result = strdup(&path[i+1]);
    return result;
}
