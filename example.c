/* example.c */
#include "arcfour.h"

#define F fflush(stdout)

void printbin(int8 *input, const int16 size) {
    int16 i;
    int8 *p;

    assert(size > 0);

    for (i=size, p=input; i; i--, p++) {
        if (!(i % 2))
            printf(" ");
        printf("%.02x", *p);
    }
    printf("\n");

    return;
}

int main(void) {
    Arcfour *rc4;
    int16 skey, stext;
    char *key, *from;
    int8 *encrypted = NULL, *decrypted = NULL;
    int status = EXIT_FAILURE;

    key = "tomatoess";
    skey = strlen(key);
    from = "Shall I compare thee to a summer's day?";
    stext = strlen(from);

    printf("Initializing encryption..."); F;
    rc4 = rc4init((int8 *)key, skey);
    if (!rc4)
        goto error;
    printf("done\n");

    printf("'%s'\n ->", from);
    encrypted = rc4encrypt(rc4, (int8 *)from, stext);
    if (!encrypted)
        goto error;
    printbin(encrypted, stext);
    rc4uninit(rc4);

    printf("Initializing decryption..."); F;
    rc4 = rc4init((int8 *)key, skey);
    if (!rc4)
        goto error;
    printf("done\n");

    decrypted = rc4decrypt(rc4, encrypted, stext);
    if (!decrypted)
        goto error;
    printf("    -> '%s'\n", (char *)decrypted);
    if (memcmp(from, decrypted, stext) == 0)
        status = EXIT_SUCCESS;
    else
        fputs("Decrypted bytes differ from input.\n", stderr);
    goto cleanup;

error:
    perror("Arcfour");
cleanup:
    rc4uninit(rc4);
    free(encrypted);
    free(decrypted);
    return status;
}
