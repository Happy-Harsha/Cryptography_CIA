#include <stdio.h>
#include <string.h>
#include <ctype.h>

void generate_key(char *text, char *key_input, char *key) {
    int text_len = strlen(text);
    int key_len = strlen(key_input);
    for (int i = 0; i < text_len; i++) {
        key[i] = key_input[i % key_len];
    }
    key[text_len] = '\0';
}

void beaufort_cipher(char *text, char *key, char *output) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i]) && isalpha(key[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            char key_base = isupper(key[i]) ? 'A' : 'a';
            output[i] = (26 + (key[i] - key_base) - (text[i] - base)) % 26 + base;
        } else {
            output[i] = text[i];
        }
    }
    output[strlen(text)] = '\0';
}

int main() {
    char text[1000], key_input[1000], key[1000], cipher[1000], plain[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key: ");
    scanf("%s", key_input);

    generate_key(text, key_input, key);

    beaufort_cipher(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    beaufort_cipher(cipher, key, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

