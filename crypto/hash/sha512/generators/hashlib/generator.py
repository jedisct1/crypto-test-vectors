#! /usr/bin/env python

import binascii
import hashlib
import os
import random
import sys

MAX_MESSAGE_LENGTH = 256

def generate():
        len = int(random.uniform(0, MAX_MESSAGE_LENGTH + 1))
        message = os.urandom(len)
        out = hashlib.sha512(message)
        print("%s\t%s" % (binascii.hexlify(message), out.hexdigest()))

count = int(sys.argv[1])

for i in xrange(0, count):
        generate()
