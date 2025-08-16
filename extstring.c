#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int extString_explode (const char *input, char separator, char ***buffer); // Array of char-arrays ("explodes" a string based on the given separator)

int extString_explode(const char *input, char separator, char ***buffer) {
    int count = 1;
    int num = 0;
    size_t len;
    for (const char *p = input; *p; p++) if (*p == separator) count++;

    fprintf(stderr, "Es sind %d Teile verfügbar.\n", count);
    sleep(5);
    *buffer = malloc(count * sizeof(char*));
    for (const char *p = input; *p; p++) {
        len++;
        if (*p == separator) {
            (*buffer)[num] = malloc(len + 1);
            printf("%d: %ld\n", num, len);
            len = 0;
            num++;
        }
    }
    pause();
}

int main () {
    char* x = "Das ist ein Test";
    char **test = NULL;
    errno = extString_explode(x, ' ', &test);
}