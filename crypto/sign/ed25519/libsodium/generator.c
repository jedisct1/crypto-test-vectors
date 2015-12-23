
#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>

#define MAX_MESSAGE_LENGTH 256

static int
generate(void)
{
    unsigned char message[MAX_MESSAGE_LENGTH];
    char          message_hex[MAX_MESSAGE_LENGTH * 2U + 1U];
    unsigned char pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char sk[crypto_sign_SECRETKEYBYTES];
    char          sk_hex[crypto_sign_SECRETKEYBYTES * 2U + 1U];
    unsigned char out[crypto_sign_BYTES];
    char          out_hex[crypto_sign_BYTES * 2U + 1U];
    size_t        len;

    len = randombytes_uniform(MAX_MESSAGE_LENGTH + 1U);
    randombytes_buf(message, len);
    crypto_sign_keypair(pk, sk);
    (void) pk;
    crypto_sign_detached(out, NULL, message, (unsigned long long) len, sk);
    sodium_bin2hex(message_hex, sizeof message_hex, message, len);
    sodium_bin2hex(sk_hex, sizeof sk_hex, sk, sizeof sk);
    sodium_bin2hex(out_hex, sizeof out_hex, out, sizeof out);
    printf("%s\t%s\t%s\n", message_hex, sk_hex, out_hex);

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
