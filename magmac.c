#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

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

    fprintf(out, "#include <stdint.h>\n\n");

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
                char ret_type[16] = "";
                if (*p == ':') {
                    p++;
                    trim_space(&p);
                    int j = 0;
                    while (*p && !isspace((unsigned char)*p) && *p != '=' && j < (int)sizeof(ret_type) - 1) {
                        ret_type[j++] = *p;
                        p++;
                    }
                    ret_type[j] = '\0';
                    trim_space(&p);
                }
                if (strncmp(p, "=>", 2) == 0) {
                    p += 2;
                    trim_space(&p);
                    const char *ctype = NULL;
                    if (strcmp(ret_type, "U8") == 0) ctype = "uint8_t";
                    else if (strcmp(ret_type, "U16") == 0) ctype = "uint16_t";
                    else if (strcmp(ret_type, "U32") == 0) ctype = "uint32_t";
                    else if (strcmp(ret_type, "U64") == 0) ctype = "uint64_t";
                    else if (strcmp(ret_type, "I8") == 0) ctype = "int8_t";
                    else if (strcmp(ret_type, "I16") == 0) ctype = "int16_t";
                    else if (strcmp(ret_type, "I32") == 0) ctype = "int32_t";
                    else if (strcmp(ret_type, "I64") == 0) ctype = "int64_t";
                    if (ret_type[0] && ctype && strncmp(p, "{}", 2) == 0) {
                        fprintf(out, "%s %s() {}\n", ctype, name);
                    } else if (strncmp(p, "{}", 2) == 0) {
                        fprintf(out, "void %s() {}\n", name);
                    } else if (strncmp(p, "true", 4) == 0) {
                        fprintf(out, "int %s() { return 1; }\n", name);
                    } else if (strncmp(p, "false", 5) == 0) {
                        fprintf(out, "int %s() { return 0; }\n", name);
                    } else if (strncmp(p, "U8", 2) == 0) {
                        fprintf(out, "uint8_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "U16", 3) == 0) {
                        fprintf(out, "uint16_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "U32", 3) == 0) {
                        fprintf(out, "uint32_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "U64", 3) == 0) {
                        fprintf(out, "uint64_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "I8", 2) == 0) {
                        fprintf(out, "int8_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "I16", 3) == 0) {
                        fprintf(out, "int16_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "I32", 3) == 0) {
                        fprintf(out, "int32_t %s() { return 0; }\n", name);
                    } else if (strncmp(p, "I64", 3) == 0) {
                        fprintf(out, "int64_t %s() { return 0; }\n", name);
                    }
                }
            }
        } else if (strncmp(p, "let", 3) == 0 && isspace((unsigned char)p[3])) {
            p += 3;
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
            if (*p == ':') {
                p++;
                trim_space(&p);
                char type[16];
                int j = 0;
                while (*p && !isspace((unsigned char)*p) && *p != '=' && j < (int)sizeof(type) - 1) {
                    type[j++] = *p;
                    p++;
                }
                type[j] = '\0';
                trim_space(&p);
                if (*p == '=') {
                    p++;
                    trim_space(&p);
                    char value[256];
                    int k = 0;
                    while (*p && *p != ';' && k < (int)sizeof(value) - 1) {
                        value[k++] = *p;
                        p++;
                    }
                    value[k] = '\0';
                    while (k > 0 && isspace((unsigned char)value[k-1])) {
                        value[--k] = '\0';
                    }
                    trim_space(&p);
                    if (*p == ';') {
                        const char *ctype = NULL;
                        if (strcmp(type, "U8") == 0) ctype = "uint8_t";
                        else if (strcmp(type, "U16") == 0) ctype = "uint16_t";
                        else if (strcmp(type, "U32") == 0) ctype = "uint32_t";
                        else if (strcmp(type, "U64") == 0) ctype = "uint64_t";
                        else if (strcmp(type, "I8") == 0) ctype = "int8_t";
                        else if (strcmp(type, "I16") == 0) ctype = "int16_t";
                        else if (strcmp(type, "I32") == 0) ctype = "int32_t";
                        else if (strcmp(type, "I64") == 0) ctype = "int64_t";
                        else if (strcmp(type, "Bool") == 0) ctype = "int";
                        const char *val = value;
                        char conv[8];
                        if (strcmp(value, "true") == 0) { strcpy(conv, "1"); val = conv; }
                        else if (strcmp(value, "false") == 0) { strcpy(conv, "0"); val = conv; }
                        if (ctype) {
                            fprintf(out, "%s %s = %s;\n", ctype, name, val);
                        }
                    }
                }
            }
        }
    }

    fclose(in);
    fclose(out);
    return EXIT_SUCCESS;
}

