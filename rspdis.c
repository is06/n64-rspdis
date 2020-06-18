#include <stdio.h>

int main() {

    FILE* source = fopen("source.bin", "rb");
    if (source == NULL) {
        printf("Unable to open source file");
        return 1;
    }

    fclose(source);

    return 0;
}
