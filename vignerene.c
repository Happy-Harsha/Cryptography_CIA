#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_key(char *text, char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key);
    for (int i = key_len; i < text_len; i++) {
        key[i] = key[i % key_len];
    }
    key[text_len] = '\0';
}

void vigenere_encrypt(char *text, char *key, char *cipher) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            cipher[i] = (text[i] - base + (key[i] - key_base)) % 26 + base;
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[strlen(text)] = '\0';
}

void vigenere_decrypt(char *cipher, char *key, char *plain) {
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            plain[i] = (cipher[i] - base - (key[i] - key_base) + 26) % 26 + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char text[1000], key_input[1000], key[1000], cipher[1000], plain[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter key: ");
    scanf("%s", key_input);

    generate_key(text, key_input);
    strcpy(key, key_input);

    vigenere_encrypt(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    vigenere_decrypt(cipher, key, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

