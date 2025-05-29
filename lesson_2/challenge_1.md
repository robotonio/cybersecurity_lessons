# Logger: Βοηθητικές Σημειώσεις & Παραδείγματα Κώδικα

---

## Περιγραφή Εργασίας

**Να δημιουργηθεί πρόγραμμα σε C που:**
- Διαβάζει γραμμές από αρχείο `input.txt`
- Τις γράφει ανά 1'' σε αρχείο log
- Αν το log αρχείο ξεπεράσει τα 30000 bytes, ξεκινά νέο με όνομα `audit_<timestamp>.log`
- Οι καταγραφές πραγματοποιούνται με **system calls** (`open`, `write`, `close`, `fstat`, `rename`)

---

## Συναρτήσεις που χρειάζονται

### Διαχείριση Αρχείων
- `int open(const char *pathname, int flags, mode_t mode);`
- `ssize_t write(int fd, const void *buf, size_t count);`
- `int close(int fd);`
- `int rename(const char *oldpath, const char *newpath);`

### Αναμονή 50ms
- `usleep(50000);  // <unistd.h>`

### Μέγεθος Αρχείου
```c
#include <sys/stat.h>
struct stat st;
fstat(fd, &st);
if (st.st_size >= 3000) {
    // rotation
}
```

### Timestamp στο Όνομα Αρχείου
```c
#include <time.h>
char filename[64];
time_t now = time(NULL);
snprintf(filename, sizeof(filename), "audit_%ld.log", now);
```

### Ανάγνωση από Αρχείο (input.txt)
```c
#include <stdio.h>
FILE *input = fopen("input.txt", "r");
char line[256];
fgets(line, sizeof(line), input);
```

---

## Τυπικό Παράδειγμα Ονόματος Log Αρχείου
```c
// audit_1716824982.log
```

---

## Tips
- Προσθέστε `\n` στο τέλος της γραμμής αν λείπει.
- Ελέγχετε αν `open()` και `fopen()` επιστρέφουν -1 ή NULL.
- Για δοκιμές, ξεκινήστε με όριο 200 bytes για να βλέπετε rotation πιο γρήγορα.
