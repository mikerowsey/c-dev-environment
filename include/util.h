#ifndef UTIL_H
#define UTIL_H

#include <stddef.h> /* size_t */

/* Return the number of elements in a fixed-size array. */
#define ARRAY_LEN(a) ((int)(sizeof(a) / sizeof((a)[0])))

/* Clamp an integer value into the inclusive range [min, max]. */
int clamp_int(int value, int min, int max);

/*
 * Safe allocation helpers.
 *
 * xmalloc / xcalloc never return NULL. If allocation fails,
 * they print an error message and terminate the program.
 */
void *xmalloc(size_t size);
void *xcalloc(size_t count, size_t size);

/*
 * Print an error message to stderr and terminate the program
 * with a non-zero exit code.
 */
void die(const char *message);

#endif /* UTIL_H */
