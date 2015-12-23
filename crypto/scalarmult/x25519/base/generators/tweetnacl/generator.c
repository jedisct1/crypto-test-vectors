
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "tweetnacl/tweetnacl.h"

static int
generate(void)
{
    unsigned char scalar[crypto_scalarmult_SCALARBYTES];
    unsigned char out[crypto_scalarmult_BYTES];
    char          scalar_hex[crypto_scalarmult_SCALARBYTES * 2U + 1U];
    char          out_hex[crypto_scalarmult_BYTES * 2U + 1U];

    randombytes(scalar, sizeof scalar);
    crypto_scalarmult_base(out, scalar);
    bin2hex(scalar_hex, sizeof scalar_hex, scalar, sizeof scalar);
    bin2hex(out_hex, sizeof out_hex, out, sizeof out);
    printf("%s\t%s\n", scalar_hex, out_hex);

    return 0;
}

int
main(int argc, char *argv[])
{
    unsigned long count;

    if (argc < 2) {
        return 1;
    }
    count = strtoul(argv[1], NULL, 10);
    while (count-- > 0UL) {
        generate();
    }
    return 0;
}
