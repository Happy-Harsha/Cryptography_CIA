#include <stdio.h>
#include <string.h>
#include <ctype.h>

void rail_fence_encrypt(char *text, int key, char *cipher) {
    int len = strlen(text);
    char rail[key][len];
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\n'; // Initialize with a placeholder
        }
    }

    int row = 0, col = 0;
    bool down = false;
    for (int i = 0; i < len; i++) {
        rail[row][col++] = text[i];
        if (row == 0 || row == key - 1)
            down = !down;

        row += down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] != '\n') {
                cipher[index++] = rail[i][j];
            }
        }
    }
    cipher[index] = '\0';
}

void rail_fence_decrypt(char *cipher, int key, char *plain) {
    int len = strlen(cipher);
    char rail[key][len];
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            rail[i][j] = '\n'; // Initialize with a placeholder
        }
    }

    int row = 0, col = 0;
    bool down = false;
    for (int i = 0; i < len; i++) {
        rail[row][col++] = '*';
        if (row == 0 || row == key - 1)
            down = !down;

        row += down ? 1 : -1;
    }

    int index = 0;
    for (int i = 0; i < key; i++) {
        for (int j = 0; j < len; j++) {
            if (rail[i][j] == '*' && index < len) {
                rail[i][j] = cipher[index++];
            }
        }
    }

    row = 0, col = 0;
    down = false;
    index = 0;
    for (int i = 0; i < len; i++) {
        plain[index++] = rail[row][col++];
        if (row == 0 || row == key - 1)
            down = !down;

        row += down ? 1 : -1;
    }
    plain[index] = '\0';
}

int main() {
    char text[1000], cipher[1000], plain[1000];
    int key;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // remove newline

    printf("Enter key: ");
    scanf("%d", &key);

    rail_fence_encrypt(text, key, cipher);
    printf("Encrypted text: %s\n", cipher);

    rail_fence_decrypt(cipher, key, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

