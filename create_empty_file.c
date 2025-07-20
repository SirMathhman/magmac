#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "empty.txt";
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("Failed to create file");
        return EXIT_FAILURE;
    }
    fclose(fp);
    printf("Created file: %s\n", filename);
    return EXIT_SUCCESS;
}
