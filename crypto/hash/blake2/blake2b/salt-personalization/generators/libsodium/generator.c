
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sodium.h>

#define MAX_MESSAGE_LENGTH 256
#define MAX_KEY_LENGTH 64
#define MAX_OUTPUT_LENGTH 64

static int
generate(void)
{
    unsigned char salt[crypto_generichash_blake2b_SALTBYTES];
    char          salt_hex[crypto_generichash_blake2b_SALTBYTES * 2U + 1U];
    unsigned char personal[crypto_generichash_blake2b_PERSONALBYTES];
    char          personal_hex[crypto_generichash_blake2b_PERSONALBYTES * 2U + 1U];
    unsigned char message[MAX_MESSAGE_LENGTH];
    char          message_hex[MAX_MESSAGE_LENGTH * 2U + 1U];
    unsigned char key[MAX_KEY_LENGTH];
    char          key_hex[MAX_KEY_LENGTH * 2U + 1U];
    unsigned char out[MAX_OUTPUT_LENGTH];
    char          out_hex[MAX_OUTPUT_LENGTH * 2U + 1U];
    size_t        message_len;
    size_t        key_len;
    size_t        out_len;

    assert(MAX_KEY_LENGTH <= crypto_generichash_blake2b_KEYBYTES_MAX);
    assert(MAX_OUTPUT_LENGTH <= crypto_generichash_blake2b_BYTES_MAX);
    randombytes_buf(salt, sizeof salt);
    randombytes_buf(personal, sizeof personal);
    message_len = randombytes_uniform(MAX_MESSAGE_LENGTH + 1U);
    randombytes_buf(message, message_len);
    key_len =
        crypto_generichash_blake2b_KEYBYTES_MIN +
        randombytes_uniform(crypto_generichash_blake2b_KEYBYTES_MAX -
                            crypto_generichash_blake2b_KEYBYTES_MIN + 1);
    randombytes_buf(key, key_len);
    out_len =
        crypto_generichash_blake2b_BYTES_MIN +
        randombytes_uniform(crypto_generichash_blake2b_BYTES_MAX -
                            crypto_generichash_blake2b_BYTES_MIN + 1);
    crypto_generichash_blake2b_salt_personal(out, out_len, message, message_len,
                                             key, key_len, salt, personal);
    sodium_bin2hex(salt_hex, sizeof salt_hex, salt, sizeof salt);
    sodium_bin2hex(personal_hex, sizeof personal_hex, personal, sizeof personal);
    sodium_bin2hex(message_hex, sizeof message_hex, message, message_len);
    sodium_bin2hex(key_hex, sizeof key_hex, key, key_len);
    sodium_bin2hex(out_hex, sizeof out_hex, out, out_len);
    printf("%s\t%s\t%s\t%s\t%zu\t%s\n", message_hex,
           key_hex, salt_hex, personal_hex, out_len, out_hex);

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
