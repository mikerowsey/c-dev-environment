#include "util.h"

#include <stdio.h>  /* fprintf, perror */
#include <stdlib.h> /* malloc, calloc, exit, EXIT_FAILURE */

/* Clamp an integer value into the inclusive range [min, max]. */
int clamp_int(int value, int min, int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}

/* Safe malloc: never returns NULL. */
void *xmalloc(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Safe calloc: never returns NULL. */
void *xcalloc(size_t count, size_t size) {
    void *ptr = calloc(count, size);
    if (!ptr) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

/* Print an error message and exit. */
void die(const char *message) {
    if (message) {
        fprintf(stderr, "%s\n", message);
    }
    exit(EXIT_FAILURE);
}
