#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/random.h>

int xor_cipher(char text[], char key[]) {
    return 0;
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
    char text[] = "password";
    int i;
    int size = strlen(text); // sizeof can be used but that includes \0 at the end 
    
    //char *key = random_key_generator(size);
    
    unsigned char key[size];
    ssize_t res = getrandom(key, sizeof(key), 0);

    for (i = 0; i < size; ++i) {
        printf("%02x", key[i]); // print hex 
    }


    return 0; 
}
