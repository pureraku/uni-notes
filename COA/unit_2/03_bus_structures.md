# 3. 🚌 Bus Structures

**Source slides:** 31--38.

## Core idea

A **bus** is a communication path used to transfer information between
the processor, memory, and peripherals.

The source focuses on three bus types:

-   **Address bus**
-   **Data bus**
-   **Control bus**

## The three buses

  Bus               What it carries       Direction in the source
  ----------------- --------------------- -------------------------
  **Address bus**   Address information   Unidirectional
  **Data bus**      Data                  Bidirectional
  **Control bus**   Control signals       Bidirectional

Think of a memory read:

``` text
CPU --address--> Memory
CPU <--data----- Memory
CPU <--/--> control signals
```

### Address lines and number of locations

If there are `x` address lines, the source gives:

$$
2^x = n
$$

where: - $x$ = number of address bits/lines - $n$ = number of selectable
locations

Example:

$$
2^3 = 8
$$

So 3 address lines can select 8 locations.

## Single, two-bus and multi-bus structures

### Single bus

One common bus connects the units.

``` mermaid
flowchart LR
    I[Input] <--> B((Common bus))
    M[Memory] <--> B
    P[Processor] <--> B
    O[Output] <--> B
```

**Problem:** devices have very different speeds. The source specifically
contrasts slow devices such as printers/keyboards with much faster
memory/processor units.

A buffer register can temporarily hold information during transfers.

### Two-bus structure

The source gives the idea that one bus can fetch instructions while
another fetches data required for execution.

**Benefit:** better operating speed.

**Cost:** more hardware/cost.

### Multi-bus structure

More buses are used to improve performance.

The source's diagram also illustrates address selection and the three
bus categories.

## Deep connection

The bus is not a computing unit.

It is the **communication infrastructure** that lets computing units
cooperate.

> **ALU computes; bus transports.**

## What to remember

### Must understand

-   Address bus → where.
-   Data bus → what data.
-   Control bus → what control action.
-   Address capacity follows $2^x=n$.
-   More buses can improve performance, but generally increase hardware
    cost/complexity.

### Low priority

Exact historical examples of devices and the drawing details of the
multi-bus slide.

## Quick check

1.  A processor has 4 address lines. How many locations can it select?
2.  During a memory read, why does the address bus need to go from CPU
    to memory while the data bus can carry data back?
3.  Why can a slow keyboard cause problems in a single-bus design?
