#include <stdio.h>
#include <string.h>

void you_win() {
    printf("Congratulations! Here is your flag: FLAG{gdb_master}\n");
}

void vuln() {
    char name[24];
    printf("Enter your name: ");
    gets(name);
    printf("Nice to meet you, %s\n", name);
}

int main() {
    vuln();
    return 0;
}
