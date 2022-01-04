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
    char *ptr;
    for (ptr = path + strlen(path) - 1; ptr >= path; --ptr) {
        if (*ptr == '/') {
            break;
        }
    }

    return strdup(ptr + 1);
}
