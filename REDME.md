# lc: ls + cat

Are you tired of running `cat` and getting an error just because the target was a directory?  
Well, here's the solution! **`lc`** is a simple command that automatically detects whether the target is a file or a directory and takes the best action:

- If it’s a **directory**, it lists its contents (like `ls`).
- If it’s a **file**, it prints its contents (like `cat`).

> ⚠️ Note: This is my very first project in C, so it’s not meant to be anything serious (for now 😄).

---

### 📁 Files

- **`lc.c`** → Main source file (production version)
- **`main.c`** → Same project, but with detailed comments in Spanish explaining each part of the code for learning purposes.

---

### 🧰 Compilation

```bash
gcc lc.c -o lc

