# Lab 1 — Operating System Installation & Basic Linux Commands

**Priority: 🔴 High**

## 🎯 Core Idea

Linux provides an operating-system environment in which programs, files, processes, permissions, and system resources can be manipulated through commands. For OS laboratory work, the terminal is especially important because later labs compile and execute C programs that interact with processes and threads.

> **Additional context:** The exact installation procedure depends on the Linux distribution and whether Linux is installed directly, in a virtual machine, or through another environment.

## 🧠 Understand It

### 1. Filesystem navigation

The shell interprets commands and starts programs for you.

```bash
pwd
ls
cd directory
cd ..
cd ~
```

- `pwd` — prints the current working directory.
- `ls` — lists directory contents.
- `cd` — changes the current directory.
- `cd ..` — moves to the parent directory.
- `cd ~` — moves to the user's home directory.

The important relationship is:

```text
Current directory
      ↓
Relative path resolution
      ↓
Command operates on the selected file/directory
```

### 2. Creating and manipulating files

```bash
mkdir os_lab
cd os_lab
touch test.c
cp test.c backup.c
mv backup.c old.c
rm old.c
rmdir empty_directory
```

`rm` removes files; `rmdir` removes empty directories.

### 3. Inspecting file contents

```bash
cat test.c
less test.c
head test.c
tail test.c
```

### 4. Compiling a C program

A common GCC workflow is:

```bash
gcc program.c -o program
./program
```

For POSIX thread programs, a typical command is:

```bash
gcc program.c -o program -pthread
```

> **Additional context:** Compiler options can vary by GCC version and program requirements.

### 5. Process-related commands

```bash
ps
ps aux
top
kill PID
```

A process is a running instance of a program. The PID uniquely identifies a process while it exists.

### 6. Permissions

```bash
ls -l
chmod u+x script.sh
```

Linux permissions are commonly represented for owner, group, and others.

## 🔗 Connections

Lab 1 supplies the environment for every later lab:

```text
Linux terminal
   ↓
Create C source
   ↓
Compile
   ↓
Execute
   ↓
Observe process/thread behavior
```

## 💡 Example

Create and run a minimal C program:

```c
#include <stdio.h>

int main(void) {
    printf("Hello, OS Lab!\n");
    return 0;
}
```

Compile:

```bash
gcc hello.c -o hello
```

Run:

```bash
./hello
```

## 📊 Comparison

| Command | Main purpose |
|---|---|
| `pwd` | Show current directory |
| `ls` | List entries |
| `cd` | Change directory |
| `mkdir` | Create directory |
| `touch` | Create/update file timestamp |
| `cp` | Copy |
| `mv` | Move/rename |
| `rm` | Remove file |
| `cat` | Display file contents |
| `ps` | Display processes |
| `kill` | Send a signal to a process |

## ⚠️ Common Confusions / Traps

- `./program` means execute a program from the current directory; typing only `program` searches the command path.
- `rm` is not the same as `rmdir`.
- A source file is not automatically an executable after writing it.
- Compilation success does not guarantee logical correctness.
- A PID identifies a process, not a source-code file.

## 📝 What to Remember

### 🔴 Must Understand
- Current vs parent vs home directory.
- Source → compiler → executable → process.
- Why process IDs matter in later labs.

### 🟡 Must Remember
- Core navigation and file commands.
- Basic GCC commands.

### 🟢 Nice to Know
- Advanced shell options and distribution-specific installation details.

## ✅ Quick Check

1. What does `pwd` tell you?
2. Why is `./program` commonly used?
3. What is the difference between a source file and a running process?
4. Which command lists processes?
5. What happens conceptually when GCC turns a C source file into an executable?
