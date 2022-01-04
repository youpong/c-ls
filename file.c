#include <string.h>

char *basedir(char *path) {
    char *result = strdup(path);
    int i;
    for(i = strlen(result); i != 0; --i) {
        if (result[i] == '/') {
            break;
        }
    }
    result[i] = '\0';

    return result;
}
