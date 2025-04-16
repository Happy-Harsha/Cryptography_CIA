#include <stdio.h>
#include <string.h>
#include <ctype.h>

int mod_inverse(int a, int m) {
    for (int i = 0; i < m; i++) {
        if ((a * i) % m == 1)
            return i;
    }
    return -1; // inverse doesn't exist
}

void affine_encrypt(char *text, int a, int b, char *cipher) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            cipher[i] = ((a * (text[i] - base) + b) % 26) + base;
        } else {
            cipher[i] = text[i];
        }
    }
    cipher[strlen(text)] = '\0';
}

void affine_decrypt(char *cipher, int a, int b, char *plain) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid 'a' value. No modular inverse exists.\n");
        return;
    }
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (isalpha(cipher[i])) {
            char base = isupper(cipher[i]) ? 'A' : 'a';
            plain[i] = (a_inv * ((cipher[i] - base - b + 26)) % 26) + base;
        } else {
            plain[i] = cipher[i];
        }
    }
    plain[strlen(cipher)] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];
    int a, b;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key 'a' (must be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter key 'b': ");
    scanf("%d", &b);

    affine_encrypt(text, a, b, cipher);
    printf("Encrypted text: %s\n", cipher);

    affine_decrypt(cipher, a, b, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

