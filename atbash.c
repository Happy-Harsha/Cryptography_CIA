#include <stdio.h>
#include <string.h>
#include <ctype.h>

void atbash_cipher(char *text, char *cipher) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            cipher[i] = 'Z' - (text[i] - 'A');
        } else if (islower(text[i])) {
            cipher[i] = 'z' - (text[i] - 'a');
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[strlen(text)] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    atbash_cipher(text, cipher);
    printf("Encrypted text: %s\n", cipher);

    atbash_cipher(cipher, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}


