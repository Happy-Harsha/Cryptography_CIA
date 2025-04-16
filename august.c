#include <stdio.h>
#include <string.h>
#include <ctype.h>

void augustus_encrypt(char *text, char *cipher) {
    int key = 1;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            cipher[i] = (text[i] - base + key) % 26 + base;
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[strlen(text)] = '\0';
}

void augustus_decrypt(char *cipher, char *plain) {
    int key = 1;
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            plain[i] = (cipher[i] - base - key + 26) % 26 + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    augustus_encrypt(text, cipher);
    printf("Encrypted text: %s\n", cipher);

    augustus_decrypt(cipher, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

