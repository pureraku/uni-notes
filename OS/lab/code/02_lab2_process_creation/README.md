# Lab 2 — Process Creation

## Programs

### `fork_pid_ppid_wait.c`
Demonstrates:
- `fork()`
- `getpid()`
- `getppid()`
- `wait()`

Compile:

```bash
gcc fork_pid_ppid_wait.c -o fork_demo
./fork_demo
```

The parent waits for the child before finishing.
