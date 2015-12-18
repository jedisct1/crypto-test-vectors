
#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>

#define MAX_MESSAGE_LENGTH 256

static int
generate(void)
{
    unsigned char message[MAX_MESSAGE_LENGTH];
    char          message_hex[MAX_MESSAGE_LENGTH * 2U + 1U];
    unsigned char out[crypto_hash_sha256_BYTES];
    char          out_hex[crypto_hash_sha256_BYTES * 2U + 1U];
    size_t        len;

    len = randombytes_uniform(MAX_MESSAGE_LENGTH + 1U);
    randombytes_buf(message, len);
    crypto_hash_sha256(out, message, (unsigned long long) len);
    sodium_bin2hex(message_hex, sizeof message_hex, message, len);
    sodium_bin2hex(out_hex, sizeof out_hex, out, sizeof out);
    printf("%s\t%s\n", message_hex, out_hex);

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
