#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/random.h>

// perform XOR cipher 
char* xor_cipher(const unsigned char text[], const unsigned char key[], int size) {
    unsigned char *xor_val = malloc(size);
    int i;

    for (i = 0; i < size; ++i) {
        xor_val[i] = text[i] ^ key[i];
    }

    return xor_val;
}

// using rand() is not cryptographically secure 
char* random_key_generator(int size) {
    const char char_sets[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQLSTUVWXYZ123456789!@#$%^&*";
    size_t set_size = sizeof(char_sets) - 1;
    int i;
    char *key = malloc(size);

    for (i = 0; i < size; ++i) {
        key[i] = char_sets[rand() % set_size];
        printf("%c\n", key[i]);
    }

    return key;
}

int main(void) {
    
    FILE *file = fopen("password.txt", "r"); // read password file
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char text[256];
    if (fgets(text, sizeof(text), file) == NULL) {
        printf("Failed to read file\n");
        fclose(file);
        return 1;
    }
    
    fclose(file);

    int i;
    int size = strlen(text); // sizeof can be used but that includes \0 at the end 
    
    //char *key = random_key_generator(size);
    
    unsigned char key[size];
    ssize_t res = getrandom(key, sizeof(key), 0);

    unsigned char *encrypted = xor_cipher(text,key,size);
    
    for (i = 0; i < size; ++i) {
        printf("%02x", encrypted[i]);
    }
    printf("\n"); 

    FILE *res_file = fopen("encrypted.txt", "w");
    for (i = 0; i < size; ++i) {
        fprintf(res_file, "%02x", (unsigned int)encrypted[i]);
    }
    fclose(res_file);

    free(encrypted);
    return 0; 
}
