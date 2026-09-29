# Operating Systems Lab — C Programs

This collection contains practical C programs for Labs 1–9.

## Structure

```text
os_lab_c_code/
├── README.md
├── 00_index.md
├── 01_lab1_linux_basics/
├── 02_lab2_process_creation/
├── 03_lab3_multithreading/
├── 04_lab4_mutual_exclusion/
├── 05_lab5_reader_writer/
├── 06_lab6_dining_philosophers/
├── 07_lab7_bankers_algorithm/
├── 08_lab8_fcfs_sjf/
├── 09_lab9_priority_round_robin/
└── study_checklist.md
```

## Environment

Programs are written for Linux/POSIX-style C.

Typical compiler:

```bash
gcc filename.c -o program
./program
```

For pthread/semaphore programs:

```bash
gcc filename.c -o program -pthread
```

## Important note

These are generated reference implementations because no institution-specific lab manual/code template was supplied. Exact input/output formats may differ from your lab sheet.

## Recommended workflow

1. Read the program logic.
2. Compile it yourself.
3. Trace the code manually.
4. Change inputs and observe the result.
5. Practice writing the core logic without copying.
