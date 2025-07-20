#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    if (access(input_file, F_OK) != 0) {
        fprintf(stderr, "Input file '%s' does not exist.\n", input_file);
        return EXIT_FAILURE;
    }

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
