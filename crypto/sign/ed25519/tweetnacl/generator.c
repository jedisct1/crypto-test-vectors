
#include <stdio.h>
#include <stdlib.h>
#include "tweetnacl/tweetnacl.h"

#define MAX_MESSAGE_LENGTH 256

static int
generate(void)
{
    unsigned char      message[MAX_MESSAGE_LENGTH];
    char               message_hex[MAX_MESSAGE_LENGTH * 2U + 1U];
    unsigned char      pk[crypto_sign_PUBLICKEYBYTES];
    unsigned char      sk[crypto_sign_SECRETKEYBYTES];
    char               sk_hex[crypto_sign_SECRETKEYBYTES * 2U + 1U];
    unsigned char      out[MAX_MESSAGE_LENGTH + crypto_sign_BYTES];
    char               out_hex[crypto_sign_BYTES * 2U + 1U];
    unsigned long long out_len;
    size_t             len;

    len = randombytes_uniform(MAX_MESSAGE_LENGTH + 1U);
    randombytes(message, len);
    crypto_sign_keypair(pk, sk);
    (void) pk;
    crypto_sign(out, &out_len, message, (unsigned long long) len, sk);
    bin2hex(message_hex, sizeof message_hex, message, len);
    bin2hex(sk_hex, sizeof sk_hex, sk, sizeof sk);
    bin2hex(out_hex, sizeof out_hex, out, crypto_sign_BYTES);
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
    count = strtoul(argv[1], NULL, 10);
    while (count-- > 0UL) {
        generate();
    }
    return 0;
}
