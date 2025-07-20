import java.io.*;

/**
 * Extremely small proof-of-concept compiler that can translate a very tiny
 * subset of Java to C. It supports a single class containing a single
 * {@code main} method where the only statement is {@code System.out.println}
 * with a string literal. The translation results in a C program containing a
 * {@code printf} call with the provided string and a trailing newline.
 */

public class Magma {
    public static void main(String[] args) throws IOException {
        // Determine source file path. By default translate the bundled example.
        String sourceFile = "examples/HelloWorld.java";
        if (args.length > 0) {
            sourceFile = args[0];
        }

        StringBuilder cBody = new StringBuilder();

        // Extremely small "parser" that only understands a println inside main.
        try (BufferedReader reader = new BufferedReader(new FileReader(sourceFile))) {
            String line;
            boolean inMain = false;
            while ((line = reader.readLine()) != null) {
                line = line.trim();

                if (line.startsWith("public static void main")) {
                    inMain = true;
                    continue;
                }
                if (inMain && line.startsWith("}")) {
                    inMain = false;
                    continue;
                }

                if (!inMain) {
                    continue;
                }

                if (line.startsWith("System.out.println")) {
                    int start = line.indexOf('(') + 1;
                    int end = line.lastIndexOf(')');
                    if (start > 0 && end > start) {
                        String content = line.substring(start, end).trim();
                        if (content.startsWith("\"") && content.endsWith("\"")) {
                            content = content.substring(0, content.length() - 1) + "\\n\"";
                        }
                        cBody.append("    printf(").append(content).append(");\n");
                    }
                }
            }
        }

        // Output a simple C program with the translated body
        try (PrintWriter writer = new PrintWriter(new FileWriter("output.c"))) {
            writer.println("#include <stdio.h>");
            writer.println("int main() {");
            writer.print(cBody.toString());
            writer.println("    return 0;");
            writer.println("}");
        }
    }
}
