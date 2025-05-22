# Challenge 4 – Self Overflow & Payload Generation 🧠

## 📘 Παράδειγμα: Ένα πρόγραμμα που κάνει overflow στον εαυτό του

Σε αυτό το παράδειγμα, θα δούμε πώς ένα C πρόγραμμα μπορεί **μόνο του**, χωρίς είσοδο από τον χρήστη, να προκαλέσει **buffer overflow** και να κατευθύνει τη ροή του προγράμματος σε μια διαφορετική συνάρτηση.

---

## 🔍 Κώδικας: `self_overflow.c`

```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Συνάρτηση-στόχος που δεν καλείται ποτέ απευθείας
void secret() {
    printf("🎉 Μπήκες στη secret()!\n");
}

// Συνάρτηση με ευπάθεια buffer overflow
void vuln() {
    char buf[32];

    // Βρίσκουμε τη διεύθυνση της secret()
    uintptr_t addr = (uintptr_t)secret;

    // Φτιάχνουμε το payload: 40 bytes μέχρι το return address
    char payload[48];
    memset(payload, 'A', 40);              // Συμπληρώνουμε buf (32) + RBP (8)
    memcpy(payload + 40, &addr, 8);        // Αντιγράφουμε τη διεύθυνση της secret()

    // Προκαλούμε το overflow
    strcpy(buf, payload);
}

int main() {
    vuln();
    printf("❌ Δεν μπήκες στη secret().\n");
    return 0;
}

