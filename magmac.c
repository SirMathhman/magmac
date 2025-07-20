#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static void trim_space(char **p) {
    while (**p && isspace((unsigned char)**p)) {
        (*p)++;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input> [output]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_file = argv[1];
    const char *output_file = (argc > 2) ? argv[2] : "out.c";

    FILE *in = fopen(input_file, "r");
    if (!in) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }
    FILE *out = fopen(output_file, "w");
    if (!out) {
        perror("Failed to open output file");
        fclose(in);
        return EXIT_FAILURE;
    }

    char line[1024];
    while (fgets(line, sizeof(line), in)) {
        char *p = line;
        trim_space(&p);
        if (strncmp(p, "fn", 2) == 0 && isspace((unsigned char)p[2])) {
            p += 2;
            trim_space(&p);
            char name[256];
            int i = 0;
            while (*p && (isalnum((unsigned char)*p) || *p == '_')) {
                if (i < (int)sizeof(name) - 1) {
                    name[i++] = *p;
                }
                p++;
            }
            name[i] = '\0';
            trim_space(&p);
            if (*p == '(' && *(p + 1) == ')') {
                p += 2;
                trim_space(&p);
                if (strncmp(p, "=>", 2) == 0) {
                    p += 2;
                    trim_space(&p);
                    if (strncmp(p, "{}", 2) == 0) {
                        fprintf(out, "void %s() {}\n", name);
                    } else if (strncmp(p, "true", 4) == 0) {
                        fprintf(out, "int %s() { return 1; }\n", name);
                    } else if (strncmp(p, "false", 5) == 0) {
                        fprintf(out, "int %s() { return 0; }\n", name);
                    }
                }
            }
        }
    }

    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}

