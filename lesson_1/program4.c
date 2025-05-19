#include <stdio.h>
#include <string.h>

void check_access() {
    char buf[32];
    int authenticated = 0;

    printf("Type password: ");
    gets(buf);

    if (authenticated) {
        printf("Access accepted!\n");
    } else {
        printf("Access denied.\n");
    }
}

int main() {
    check_access();
    return 0;
}
