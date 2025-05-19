
#include <stdio.h>
#include <string.h>

void vuln() {
    char buf[32];
    printf("Δώσε δεδομένα: ");
    gets(buf);  // επικίνδυνη συνάρτηση
    printf("Τέλος vuln()\n");
}

int main() {
    vuln();
    return 0;
}
