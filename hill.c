#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 2

int mod26(int x) {
    return (x % 26 + 26) % 26;
}

void get_key_matrix(int key_matrix[SIZE][SIZE], char *key_str) {
    for (int i = 0, k = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++, k++) {
            key_matrix[i][j] = tolower(key_str[k]) - 'a';
        }
    }
}

void get_inverse_key(int key[SIZE][SIZE], int inverse[SIZE][SIZE]) {
    int det = key[0][0]*key[1][1] - key[0][1]*key[1][0];
    det = mod26(det);

    int det_inv = -1;
    for (int i = 0; i < 26; i++) {
        if ((det * i) % 26 == 1) {
            det_inv = i;
            break;
        }
    }
    if (det_inv == -1) {
        printf("Key matrix is not invertible modulo 26.\n");
        return;
    }

    inverse[0][0] = mod26(key[1][1] * det_inv);
    inverse[0][1] = mod26(-key[0][1] * det_inv);
    inverse[1][0] = mod26(-key[1][0] * det_inv);
    inverse[1][1] = mod26(key[0][0] * det_inv);
}

void process_text_blocks(char *text, int blocks[][SIZE], int *len) {
    int i = 0, k = 0;
    while (text[i] != '\0') {
        for (int j = 0; j < SIZE; j++) {
            if (text[i] == '\0') {
                blocks[k][j] = 'x' - 'a'; // padding
            } else if (isalpha(text[i])) {
                blocks[k][j] = tolower(text[i]) - 'a';
                i++;
            } else {
                i++;
                j--; // skip non-alpha
            }
        }
        k++;
    }
    *len = k;
}

void apply_hill(int key[SIZE][SIZE], int in[][SIZE], int out[][SIZE], int count) {
    for (int b = 0; b < count; b++) {
        for (int i = 0; i < SIZE; i++) {
            out[b][i] = 0;
            for (int j = 0; j < SIZE; j++) {
                out[b][i] += key[i][j] * in[b][j];
            }
            out[b][i] = mod26(out[b][i]);
        }
    }
}

void blocks_to_text(int blocks[][SIZE], int count, char *result) {
    int k = 0;
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < SIZE; j++) {
            result[k++] = blocks[i][j] + 'a';
        }
    }
    result[k] = '\0';
}

int main() {
    char text[1000], key_str[SIZE*SIZE+1], cipher[1000], plain[1000];
    int key[SIZE][SIZE], inv_key[SIZE][SIZE];
    int blocks[500][SIZE], result[500][SIZE], count;

    printf("Enter text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter 4-letter key: ");
    scanf("%s", key_str);

    get_key_matrix(key, key_str);
    get_inverse_key(key, inv_key);

    process_text_blocks(text, blocks, &count);

    apply_hill(key, blocks, result, count);
    blocks_to_text(result, count, cipher);
    printf("Encrypted text: %s\n", cipher);

    apply_hill(inv_key, result, blocks, count);
    blocks_to_text(blocks, count, plain);
    printf("Decrypted text: %s\n", plain);

    return 0;
}

