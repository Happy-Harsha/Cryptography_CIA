#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_key(char *text, char *key_input, int *key) {
    int text_len = strlen(text);
    int key_len = strlen(key_input);
    for (int i = 0; i < text_len; i++) {
        if (isdigit(key_input[i % key_len])) {
            key[i] = key_input[i % key_len] - '0';
        } else {
            key[i] = 0; // default shift for non-digit
        }
    }
}

void gronsfeld_encrypt(char *text, int *key, char *cipher) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            cipher[i] = (text[i] - base + key[i]) % 26 + base;
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[strlen(text)] = '\0';
}

void gronsfeld_decrypt(char *cipher, int *key, char *plain) {
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            plain[i] = (cipher[i] - base - key[i] + 26) % 26 + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char text[1000], key_input[100], cipher[1000], plain[1000];
    int key[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter numeric key (digits only): ");
    scanf("%s", key_input);

    generate_key(text, key_input, key);

    gronsfeld_encrypt(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    gronsfeld_decrypt(cipher, key, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

