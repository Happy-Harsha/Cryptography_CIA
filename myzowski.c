#include <stdio.h>
#include <string.h>
#include <ctype.h>

void fill_matrix(char *text, int rows, int cols, char matrix[rows][cols]) {
    int len = strlen(text);
    int index = 0;

    // Fill matrix with text, padding with 'x' if necessary
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < len) {
                matrix[i][j] = text[index++];
            } else {
                matrix[i][j] = 'x'; // Padding
            }
        }
    }
}

void encrypt_myzowski(char *text, int key_len, char *cipher) {
    int len = strlen(text);
    int rows = (len + key_len - 1) / key_len;  // Calculate number of rows
    int cols = key_len;  // Key length determines number of columns

    char matrix[rows][cols];
    fill_matrix(text, rows, cols, matrix);

    // Read columns for cipher text
    int index = 0;
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            cipher[index++] = matrix[i][j];
        }
    }
    cipher[index] = '\0';
}

void decrypt_myzowski(char *cipher, int key_len, char *plain) {
    int len = strlen(cipher);
    int rows = (len + key_len - 1) / key_len;  // Calculate number of rows
    int cols = key_len;  // Key length determines number of columns

    char matrix[rows][cols];
    int index = 0;

    // Fill matrix with cipher text column by column
    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < rows; i++) {
            if (index < len) {
                matrix[i][j] = cipher[index++];
            } else {
                matrix[i][j] = 'x'; // Padding
            }
        }
    }

    // Read rows for plain text
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            plain[index++] = matrix[i][j];
        }
    }
    plain[index] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];
    int key_len;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key length: ");
    scanf("%d", &key_len);

    encrypt_myzowski(text, key_len, cipher);
    printf("Encrypted text: %s\n", cipher);

    decrypt_myzowski(cipher, key_len, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

