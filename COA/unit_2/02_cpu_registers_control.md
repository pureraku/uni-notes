# 2. ⚙️ CPU, Registers and Control

**Source slides:** 13--30.

## Core idea

The CPU is the computer's main processing unit. Its three central
components in the source are the **ALU, Control Unit, and Registers**.

The most useful way to understand registers is by asking:

> **What information does the CPU need to keep immediately available
> while it works?**

## Registers

The source defines registers as fast, stand-alone storage locations that
hold data temporarily.

### Important registers

  -----------------------------------------------------------------------
  Register                            Purpose
  ----------------------------------- -----------------------------------
  **MAR --- Memory Address Register** Holds the address involved in a
                                      memory transfer.

  **MDR --- Memory Data Register**    Holds the data involved in a memory
                                      transfer.

  **IR --- Instruction Register**     Holds the instruction currently
                                      being executed.

  **PC --- Program Counter**          Points to the next instruction to
                                      be fetched.

  **General-purpose registers**       Hold data and intermediate results;
                                      also called scratch-pad registers.
  -----------------------------------------------------------------------

### Why MAR and MDR are separate

A memory transfer needs two different pieces of information:

``` text
MAR → "WHERE?"
MDR → "WHAT DATA?"
```

### PC and IR: don't confuse them

-   **PC** → address of the **next instruction to fetch**
-   **IR** → instruction **currently being executed**

So the CPU needs both:

``` text
PC → "Where is the next instruction?"
IR → "What instruction am I working on now?"
```

## Registers vs memory

The source explicitly states that general-purpose register access is
faster than cache access.

That is why registers are used for immediate working data and
intermediate results.

## What to remember

### Must understand

-   `MAR` stores an **address**.
-   `MDR` stores **data**.
-   `IR` stores the **current instruction**.
-   `PC` points to the **next instruction to fetch**.
-   General-purpose registers hold temporary data/intermediate results.

### Common trap

**PC does not mean "current instruction."** The source assigns that role
to the **IR**.

## Quick check

1.  If the CPU wants to read memory location `500`, which register
    should hold `500`?
2.  Where would the data read from location `500` be held during the
    transfer?
3.  After fetching an instruction, why does the CPU need both the PC and
    IR?
