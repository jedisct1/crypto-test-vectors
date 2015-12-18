
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>

static int
generate(void)
{
    unsigned char ge[crypto_scalarmult_BYTES];
    unsigned char out[crypto_scalarmult_BYTES];
    unsigned char scalar[crypto_scalarmult_SCALARBYTES];
    char          ge_hex[crypto_scalarmult_BYTES * 2U + 1U];    
    char          out_hex[crypto_scalarmult_BYTES * 2U + 1U];
    char          scalar_hex[crypto_scalarmult_SCALARBYTES * 2U + 1U];

    randombytes_buf(scalar, sizeof scalar);
    randombytes_buf(ge, sizeof ge);
    if (crypto_scalarmult(out, scalar, ge) != 0) {
        return -1;
    }
    sodium_bin2hex(scalar_hex, sizeof scalar_hex, scalar, sizeof scalar);
    sodium_bin2hex(ge_hex, sizeof ge_hex, ge, sizeof ge);
    sodium_bin2hex(out_hex, sizeof out_hex, out, sizeof out);
    printf("%s\t%s\t%s\n", scalar_hex, ge_hex, out_hex);

    return 0;
}

int
main(int argc, char *argv[])
{
    unsigned long count;

    if (argc < 2) {
        return 1;
    }
    if (sodium_init() != 0) {
        return 1;
    }
    count = strtoul(argv[1], NULL, 10);
    while (count-- > 0UL) {
        generate();
    }
    return 0;
}
