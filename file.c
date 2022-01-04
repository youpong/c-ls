#include <string.h>

char *basedir(char *path) {
    char *result = strdup(path);
    int i;
    for(i = strlen(result) - 1; i >= 0; --i) {
        if (result[i] == '/') {
            result[i+1] = '\0';
            return result;
        }
    }
    result[0] = '\0';
    return result;
}

char *filename(char *path) {
    //  for(i = 
    //    $path =~ m'([^/]*)$';
    //    return $1;
    return NULL;
}
