# 9. 🔬 Microprocessors

**Source slides:** 104--114.

## Core idea

The source defines a **microprocessor** as a CPU on a single chip.

A **microcontroller** combines a microprocessor with associated support
circuitry, memory, and peripheral I/O components on a single chip.

![Microprocessor vs microcontroller --- source
diagram](assets/microprocessor-vs-microcontroller.png)

## Microprocessor vs microcontroller

The source's comparison emphasizes:

  -----------------------------------------------------------------------
  Microprocessor                      Microcontroller
  ----------------------------------- -----------------------------------
  CPU is standalone; RAM, ROM, I/O,   CPU, RAM, ROM, I/O and timer are on
  timer are separate                  one chip

  Designer can choose amount of       Fixed on-chip amounts
  ROM/RAM/I/O                         

  More expensive in the source        Less expensive
  comparison                          

  General purpose                     Single purpose

  More complex system design          Simpler, cost-effective design
  -----------------------------------------------------------------------

### Main conceptual difference

``` text
Microprocessor → processing core + external components
Microcontroller → processing + memory + I/O integrated
```

## Internal structure

The source's microprocessor block diagram contains:

-   ALU
-   Register section
-   Control and timing section
-   Address bus
-   Data bus
-   Control bus

![Microprocessor block diagram ---
source](assets/microprocessor-block.png)

## Three main tasks of a microprocessor

The source lists:

1.  Data transfer between itself and memory/I/O.
2.  Simple arithmetic and logic operations.
3.  Program flow via simple decisions.

This is a useful summary of the whole unit:

> **move data → transform data → decide what happens next**

## Types of microprocessors

The source says microprocessors can be characterized by:

-   **Word size** --- 8-bit, 16-bit, 32-bit, etc.
-   **Instruction-set structure** --- RISC or CISC.
-   **Function** --- general-purpose or special-purpose.

## Evolution listed in the source

  Generation       Size Source examples/notes
  ------------ -------- ---------------------------------------------------
  First           4-bit Intel 4004; simple arithmetic/logic and control
  Second          8-bit 8-bit arithmetic/logic
  Third          16-bit 8086, Zilog Z800, 80286
  Fourth         32-bit Intel 80386 cited
  Fifth          64-bit Pentium family and multiprocessing examples cited

### Low priority

The historical timeline and list of "typical microprocessors" are mostly
factual recall.

Know the broad pattern:

> **word size increased across generations.**

Do not spend your first study session memorizing the whole list.

## What to remember

### Must understand

-   Microprocessor = CPU on a single chip.
-   Microcontroller = processing + associated memory/I/O/support
    integrated on one chip, according to the source.
-   Microprocessor block: ALU + registers + control/timing + buses.
-   Microprocessor tasks: transfer, compute, control flow.

### Low priority

Exact historical dates, company lists, and the full generation list.

## Quick check

1.  If memory and I/O are integrated onto the same chip as the CPU, is
    the source describing a microprocessor or microcontroller?
2.  Why does the microprocessor still need buses if the CPU contains the
    ALU and registers?
3.  What three broad tasks does the source assign to a microprocessor?
