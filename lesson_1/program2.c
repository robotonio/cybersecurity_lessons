
#include <stdio.h>
#include <string.h>

void vuln() {
    char buf[32];
    printf("Input data: ");
    gets(buf);  //danger
    printf("End of vuln()\n");
}

int main() {
    vuln();
    return 0;
}
