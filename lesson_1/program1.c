#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show_memory() {
    int a = 42;
    int *b = malloc(sizeof(int));
    *b = 99;

    char buf[16];
    strcpy(buf, "Hello");

    printf("buf: %p\n", (void*)buf);
    printf("&a: %p\n", (void*)&a);
    printf("b (heap): %p\n", (void*)b);
    printf("&b (stack): %p\n", (void*)&b);

    free(b);
}

int main() {
    show_memory();
    return 0;
}
