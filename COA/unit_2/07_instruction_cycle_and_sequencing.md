# 7. 🔄 Instruction Cycle, Sequencing and Condition Codes

**Source slides:** 75--83.

## Core idea

The **instruction cycle** is the repeated process by which the CPU
processes instructions.

The source calls it the **fetch-decode-execute cycle** and gives four
steps:

1.  Fetch instruction
2.  Decode instruction
3.  Read effective address
4.  Execute instruction

``` mermaid
flowchart LR
    F[1. Fetch] --> D[2. Decode]
    D --> E[3. Read effective address]
    E --> X[4. Execute]
    X --> F
```

## Step 1 --- Fetch

The instruction is fetched from the memory address contained in the
**PC** and placed in the **IR**.

Conceptually:

``` text
PC → memory address
memory → IR
```

Then the PC moves toward the next instruction.

> **Source nuance:** one slide says the PC is incremented by 1 after
> fetch; a later example uses `+4` because the example assumes 4-byte
> instructions. Treat the increment as dependent on the
> instruction/memory organization rather than memorizing "always +1".

## Step 2 --- Decode

The instruction in the IR is interpreted so the processor knows what
operation is required.

## Step 3 --- Read effective address

If the instruction uses an indirect address, the effective address must
be obtained.

Otherwise, for an immediate operand, the operand is directly available
from the instruction.

This is why **addressing modes** matter: they determine how the CPU
finds the operand.

## Step 4 --- Execute

The Control Unit sends control signals to the appropriate CPU functional
units.

The result may be: - stored in a register, - stored in memory, - or sent
to an output device.

Then the cycle repeats.

## Straight-line sequencing

In **straight-line sequencing**, instructions execute sequentially.

The PC is incremented by a fixed offset, and no branch address is
loaded.

Example from the source:

If instructions occupy 4 bytes and the first instruction is at address
`i`:

``` text
i
↓
i+4
↓
i+8
↓
i+12
...
```

The source calls this **straight-line sequencing**.

## What changes in a loop?

A loop breaks the simple pattern.

Instead of always continuing to the next sequential address, the PC is
loaded with a **branch address**.

The source's "add n numbers" example uses: - `R0` for the running sum, -
`R1` as a counter, - location `N` for the number of iterations, - `LOOP`
as the repeated branch target, - `SUM` for the final result.

``` mermaid
flowchart TD
    A[Load n into R1] --> B[Clear R0]
    B --> C[LOOP: add next number to R0]
    C --> D[Decrement R1]
    D --> E{R1 = 0?}
    E -- No --> C
    E -- Yes --> F[Store result in SUM]
```

## Condition codes

The processor keeps information about operation results for later
conditional branching.

The source lists:

  Code    Meaning    Set to 1 when...
  ------- ---------- ----------------------------
  **N**   Negative   Result is negative
  **Z**   Zero       Result is zero
  **V**   Overflow   Arithmetic overflow occurs
  **C**   Carry      Carry occurs from the MSB

These flags let later instructions make decisions.

### Why flags matter

A processor can perform:

``` text
operation → result + status information
```

Then a conditional branch can use the status.

So:

> **The arithmetic operation produces information that the control flow
> can consume.**

## What to remember

### Must understand

-   Instruction cycle = fetch → decode → effective-address step →
    execute.
-   PC identifies where to fetch; IR holds the fetched instruction.
-   Straight-line sequencing increments PC without loading a branch
    target.
-   Loops require a change to the PC/branch target.
-   Condition codes summarize important properties of an operation's
    result.

### Must remember

`N, Z, V, C`: - Negative - Zero - Overflow - Carry

## Quick check

1.  Why is the PC needed during fetch?
2.  What must change when a loop jumps back to `LOOP`?
3.  If an arithmetic result is zero, which condition code becomes 1?
