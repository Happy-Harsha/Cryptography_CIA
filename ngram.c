#include <stdio.h>
#include <string.h>
#include <ctype.h>

void ngram_encrypt(char *text, int n, char *cipher) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int shift = 0;
            for (int j = 0; j < n && i + j < len; j++) {
                if (isalpha(text[i + j])) {
                    shift += tolower(text[i + j]) - 'a';
                }
            }
            cipher[i] = (text[i] - base + (shift % 26)) % 26 + base;
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[len] = '\0';
}

void ngram_decrypt(char *cipher, int n, char *text) {
    int len = strlen(cipher);
    char prev[1000] = {0};
    for (int i = 0; i < len; i++) {
        prev[i] = text[i]; // placeholder for building known plaintext
    }

    for (int i = 0; i < len; i++) {
        if (isalpha(cipher[i])) {
            int shift = 0;
            for (int j = 0; j < n && i + j < len; j++) {
                if (i + j < i) {
                    shift += tolower(prev[i + j]) - 'a';
                }
            }
            char base = isupper(cipher[i]) ? 'A' : 'a';
            text[i] = (cipher[i] - base - (shift % 26) + 26) % 26 + base;
            prev[i] = text[i];
        } else {
            text[i] = cipher[i];
        }
    }
    text[len] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];
    int n;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter n-gram size: ");
    scanf("%d", &n);

    ngram_encrypt(text, n, cipher);
    printf("Encrypted text: %s\n", cipher);

    ngram_decrypt(cipher, n, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

