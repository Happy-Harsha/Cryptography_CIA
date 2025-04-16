#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_autokey(char *text, char *key_input, char *key) {
    int key_len = strlen(key_input);
    int text_len = strlen(text);
    strcpy(key, key_input);
    for (int i = key_len; i < text_len; i++) {
        key[i] = text[i - key_len];
    }
    key[text_len] = '\0';
}

void autokey_encrypt(char *text, char *key, char *cipher) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i]) && isalpha(key[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            cipher[i] = (text[i] - base + (key[i] - key_base)) % 26 + base;
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[strlen(text)] = '\0';
}

void autokey_decrypt(char *cipher, char *key_input, char *plain) {
    int cipher_len = strlen(cipher);
    char key[1000];
    strcpy(key, key_input);
    for (int i = 0; i < cipher_len; i++) {
        if (isalpha(cipher[i]) && isalpha(key[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            plain[i] = (cipher[i] - base - (key[i] - key_base) + 26) % 26 + base;
            key[i + strlen(key_input)] = plain[i]; // extend key with plain text
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[cipher_len] = '\0';
}

int main() {
    char text[1000], key_input[1000], key[1000], cipher[1000], plain[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key: ");
    scanf("%s", key_input);

    generate_autokey(text, key_input, key);

    autokey_encrypt(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    autokey_decrypt(cipher, key_input, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

