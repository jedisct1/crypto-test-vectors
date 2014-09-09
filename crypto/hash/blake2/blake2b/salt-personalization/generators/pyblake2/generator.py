#! /usr/bin/env python

import binascii
import os
import random
import sys
from   pyblake2 import blake2b

SALT_LENGTH = 16
PERSONAL_LENGTH = 16
MAX_MESSAGE_LENGTH = 256
MAX_KEY_LENGTH = 64
MAX_OUTPUT_LENGTH = 64

def generate():
        messageLen = int(random.uniform(0, MAX_MESSAGE_LENGTH + 1))
        message = os.urandom(messageLen)
        keyLen = int(random.uniform(0, MAX_KEY_LENGTH + 1))
        key = os.urandom(keyLen)
        salt = os.urandom(SALT_LENGTH)
        personal = os.urandom(PERSONAL_LENGTH)
        outLen = int(random.uniform(1, MAX_OUTPUT_LENGTH + 1))
        if key:
            out = blake2b(data = message, key = key, digest_size = outLen, salt = salt, person = personal)
        else:
            out = blake2b(data = message, digest_size = outLen, salt = salt, person = personal)

        print("%s\t%s\t%s\t%s\t%u\t%s" % (binascii.hexlify(message), binascii.hexlify(key), binascii.hexlify(salt), binascii.hexlify(personal), outLen, out.hexdigest()))

count = int(sys.argv[1])

for i in xrange(0, count):
        generate()
