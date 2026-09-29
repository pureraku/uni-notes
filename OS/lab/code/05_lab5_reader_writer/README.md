# Lab 5 — Reader-Writer Problem

`reader_writer.c` implements a common reader-preference solution.

Compile:

```bash
gcc reader_writer.c -o reader_writer -pthread
./reader_writer
```

The first reader locks the shared resource and the last reader releases it. Writers require exclusive access.

This is a teaching implementation; reader preference can cause writer starvation under sustained reader activity.
