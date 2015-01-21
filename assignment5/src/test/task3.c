#include <swap_endianness.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
	if (argc < 3) {
		printf("Usage: %s [16|32] file\n", argv[0]);
		return 1;
	}

	int bit_count = atoi(argv[1]);
	if (bit_count != 16 && bit_count != 32) {
		printf("Unknown bit count\n");
		return 2;
	}
	FILE *f = fopen(argv[2], "r");
	if (!f) {
		printf("Cannot open %s for reading\n", argv[2]);
		return 3;
	}

	/********************************************************/
	/* 3. Test your functions from swap_endianness.h with
	   this program. Read the right number of bytes from f,
	   swap their endianness and print them as integers.
	*/

	/********************************************************/

	return 0;
}
