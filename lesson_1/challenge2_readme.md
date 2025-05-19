# Challenge: Bypass the Gatekeeper

## Description:

You are given the following vulnerable C program:

```c
#include <stdio.h>
#include <string.h>

void secret_function() {
    printf("ACCESS GRANTED: FLAG{gdb_advanced_user}\n");
}

void gatekeeper() {
    printf("Access denied.\n");
}

void vuln() {
    char input[40];
    printf("Enter passcode: ");
    gets(input);
    gatekeeper();
}

int main() {
    vuln();
    return 0;
}
```

The program is compiled without protections:

```bash
gcc -g -fno-stack-protector -no-pie -z execstack gatekeeper.c -o gatekeeper
```

---

## Objective:

Your mission is to redirect execution from the `gatekeeper()` function to the `secret_function()` **without modifying the source code**.

---

## Constraints:

- You are only allowed to provide input via standard input (stdin).
- You must use GDB to discover the necessary addresses.
- You must **overwrite the return address of `vuln()`**, even though the program calls `gatekeeper()` before returning.

---

## Hint:

Although `gatekeeper()` is called after the buffer, the vulnerable `gets(input)` runs **before** it, allowing you to overwrite the return address of `vuln()`.

---

## Deliverable:

Provide:
1. The address of `secret_function()` (from GDB).
2. The exact payload used (in Python).
3. The output showing the flag.

---

## Expected Behavior:

```
Enter passcode: ACCESS GRANTED: FLAG{gdb_advanced_user}
Segmentation fault (core dumped)
```


