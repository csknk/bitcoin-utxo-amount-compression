#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include "integer-input.h"
#include "print-int.h"

// Amount compression:
// * If the amount is 0, output 0
// * first, divide the amount (in base units) by the largest power of 10 possible; call the exponent e (e is max 9)
// * if e<9, the last digit of the resulting number cannot be 0; store it as d, and drop it (divide by 10)
//   * call the result n
//   * output 1 + 10*(9*n + d - 1) + e
// * if e==9, we only know the resulting number is not zero, so output 1 + 10*(n - 1) + 9
// (this is decodable, as d is in [1-9] and e is in [0-9])

uint64_t CompressAmount(uint64_t n)
{
	if (n == 0)
		return 0;
	int e = 0;
	while (((n % 10) == 0) && e < 9) {
		n /= 10;
		e++;
	}
	if (e < 9) {
		int d = (n % 10);
		assert(d >= 1 && d <= 9);
		n /= 10;
		return 1 + (n*9 + d - 1)*10 + e;
	} else {
		return 1 + (n - 1)*10 + 9;
	}
}

uint64_t DecompressAmount(uint64_t x)
{
	// x = 0  OR  x = 1+10*(9*n + d - 1) + e  OR  x = 1+10*(n - 1) + 9
	if (x == 0)
		return 0;
	x--;
	// x = 10*(9*n + d - 1) + e
	int e = x % 10;
	x /= 10;
	uint64_t n = 0;
	if (e < 9) {
		// x = 9*n + d - 1
		int d = (x % 9) + 1;
		x /= 9;
		// x = n
		n = x*10 + d;
	} else {
		n = x+1;
	}
	while (e) {
		n *= 10;
		e--;
	}
	return n;
}

int main()
{
	int n = 0;
	printf("Enter a number to compress: ");
	intFromStdin(&n);
	printf("Bytes uncompressed:\t");
	printInt(&n, sizeof(n));
	printf("Bytes compressed:\t");
	uint64_t comp = CompressAmount((uint64_t)n);
       	printInt(&comp, sizeof(comp));
	printf("Compressed, decimal:\t%lu\n", comp);
	return 0;
}
