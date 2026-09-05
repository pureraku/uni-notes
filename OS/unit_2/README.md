# Unit 2 — C Code Cheat Sheet

This pack is based on the uploaded Unit 2 material's synchronization topics, especially:
- Critical-section problem
- Peterson's solution
- Synchronization hardware
- Mutex locks
- Semaphores
- Bounded-buffer / producer-consumer
- Dining philosophers
- Readers-writers
- Monitors

The Markdown files are the exam-facing notes. Matching `.c` files are included so the examples can be copied and compiled directly.

## Compile

On Linux/macOS with GCC:

```bash
gcc 00_critical_section.c -pthread
gcc 01_petersons_solution.c -pthread -std=c11
gcc 02_test_and_set.c -pthread -std=c11
gcc 03_swap_lock.c -pthread -std=c11
gcc 04_mutex_lock.c -pthread
gcc 05_semaphores.c -pthread
gcc 06_producer_consumer.c -pthread
gcc 07_dining_philosophers.c -pthread
gcc 08_readers_writers.c -pthread
gcc 09_monitors.c -pthread
```

## Important

The textbook pseudocode for Peterson, test-and-set, and swap is shown alongside real C implementations. Real C needs atomic operations or OS synchronization primitives to make shared-memory synchronization well-defined.

The dining-philosophers example intentionally shows the basic resource-acquisition pattern from the classic problem; its purpose is to recognize the deadlock scenario, not to provide a production deadlock-free implementation.
