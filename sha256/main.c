#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// sha256 padding rules: 
// 1. append a single 1 bit, followed by seven 0 bits 
// 2. append enough zero bytes so that the input length is 56 bytes mod 64. 
// 3. append the original input length in bits as an 8 byte(64 bits) big-endian integer. 

int main(void) {
    FILE *file = fopen("input.txt","r");
    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    uint8_t input[64]; // stores exactly 8 bits in each index 
    // fread returns a size_t representing the number of elements read 
    // size_t is an unsigned int type used to represent the size of objects in memory, such as arrays, strings, and allocated memory.
    size_t input_size = fread(input, 1, sizeof(input), file);

    if(ferror(file)) {
        perror("fread");
        fclose(file);
        return 1;
    }

    fclose(file);
    printf("Bytes read: %zu\n", input_size);

    return 0;
}
