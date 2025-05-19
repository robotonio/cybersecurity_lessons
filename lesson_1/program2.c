#include <stdio.h>
#include <string.h>

void secret() {
    printf("You are in secret()!\n");
}

void vuln() {
    char buf[32];
    printf("Give input: ");
    gets(buf);
    printf("End vuln()\n");
}

int main() {
    printf("Address of secret: %p\n", secret);
    vuln();
    return 0;
}
