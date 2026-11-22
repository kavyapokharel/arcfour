Arcfour
=======

A small RC4 implementation in C. The example encrypts a line of Shakespeare,
prints the bytes in hex, then decrypts them and checks the result. RC4 is
obsolete; this code is for studying the cipher.

Building
--------

From the project directory, run:

    make
    ./example

Tested on macOS with Apple Clang. The default target builds the shared library
(`arcfour.so`) and the example program. Run `make clean` to remove the build
products.

The key and message are set in `example.c`. With the supplied key
(`tomatoess`), the output is:

```text
Initializing encryption...done
'Shall I compare thee to a summer's day?'
 ->53 68ff cac1 391f 2e8d a77c 36a8 f63c 1902 5fb1 e181 def3 e790 88ea 5df5 37f7 6fae 9d80 585e d9b5
Initializing decryption...done
    -> 'Shall I compare thee to a summer's day?'
```

Library notes
-------------

Include `arcfour.h` and link with `arcfour.o` as the example does.
`rc4init(key, len)` takes a key of 1 to 256 bytes. It shuffles a 256-byte
table, then discards the first 500 million bytes of keystream. This accounts
for the pause at startup. When comparing output with another implementation,
start both at the same offset.

`rc4encrypt(state, data, len)` XORs each input byte with the next byte of
keystream. Successive calls on the same state continue where the last call
left off. To decrypt from the beginning, initialize a fresh state with the
same key and call `rc4decrypt`, which is a macro for the same routine.

Keep the byte count alongside the ciphertext: a zero byte can occur anywhere
in the result. Both initialization and encryption can return `NULL`. Free
each output buffer with `free` and release the state with `rc4uninit`.
