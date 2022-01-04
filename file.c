#include <string.h>

char *basedir(char *path) {
    char *result = strdup(path);
    int i;
    for(i = strlen(result); i >= 0; --i) {
        if (result[i] == '/') {
            result[i+1] = '\0';
            return result;
        }
    }
    result[0] = '\0';
    return result;
}
