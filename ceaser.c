#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char *text, int key, char *cipher) {
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

void decrypt(char *cipher, int key, char *plain) {
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
    int key;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key: ");
    scanf("%d", &key);

    encrypt(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    decrypt(cipher, key, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

