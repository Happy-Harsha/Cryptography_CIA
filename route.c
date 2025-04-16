#include <stdio.h>
#include <string.h>
#include <ctype.h>

void route_cipher_encrypt(char *text, int rows, int cols, char *cipher) {
    int len = strlen(text);
    char grid[rows][cols];

    // Fill grid with text, padding with 'x' if needed
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < len) {
                grid[i][j] = text[index++];
            } else {
                grid[i][j] = 'x'; // padding character
            }
        }
    }

    // Read the grid in a zigzag pattern (row-wise)
    index = 0;
    for (int j = 0; j < cols; j++) {
        if (j % 2 == 0) {  // Move down the column
            for (int i = 0; i < rows; i++) {
                cipher[index++] = grid[i][j];
            }
        } else {  // Move up the column
            for (int i = rows - 1; i >= 0; i--) {
                cipher[index++] = grid[i][j];
            }
        }
    }
    cipher[index] = '\0';
}

void route_cipher_decrypt(char *cipher, int rows, int cols, char *plain) {
    int len = strlen(cipher);
    char grid[rows][cols];

    // Fill grid with cipher text
    int index = 0;
    for (int j = 0; j < cols; j++) {
        if (j % 2 == 0) {  // Move down the column
            for (int i = 0; i < rows; i++) {
                grid[i][j] = cipher[index++];
            }
        } else {  // Move up the column
            for (int i = rows - 1; i >= 0; i--) {
                grid[i][j] = cipher[index++];
            }
        }
    }

    // Read the grid row-wise to get the plain text
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            plain[index++] = grid[i][j];
        }
    }
    plain[index] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];
    int rows, cols;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter number of rows: ");
    scanf("%d", &rows);

    printf("Enter number of columns: ");
    scanf("%d", &cols);

    route_cipher_encrypt(text, rows, cols, cipher);
    printf("Encrypted text: %s\n", cipher);

    route_cipher_decrypt(cipher, rows, cols, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

