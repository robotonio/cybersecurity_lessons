#include <stdio.h>
#include <string.h>

void secret() {
    printf("🎉 Είσαι μέσα στη secret()!\n");
}

void vuln() {
    char buf[32];
    printf("Δώσε input: ");
    gets(buf);
    printf("Τέλος vuln()\n");
}

int main() {
    printf("Διεύθυνση της secret: %p\n", secret);
    vuln();
    return 0;
}
