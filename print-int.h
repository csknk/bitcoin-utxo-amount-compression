#ifndef PRINT_INT_H
#define PRINT_INT_H 

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

/**
 * Print an integer - any width.
 * */
void printInt(void *p, size_t width)
{
	unsigned char *bytes = (unsigned char *)(p);
	for (ssize_t i = width - 1; i >= 0; --i) {
		printf("%02x ", *(bytes + i));
	}  
	printf("\n");
}

#endif /* PRINT-INT_H */
