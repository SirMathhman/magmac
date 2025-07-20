# MagmaC

MagmaC aims to be a self-hosted compiler written in a restricted subset of Java. The compiler will translate programs from this subset of Java to C.

## Example

The following `HelloWorld.java` demonstrates the target language:

```java
class HelloWorld {
    public static void main() {
        System.out.println("Hello, world!");
    }
}
```

Running the compiler on this file produces the following C code:

```c
#include <stdio.h>
int main() {
    printf("Hello, world!\n");
    return 0;
}
```
