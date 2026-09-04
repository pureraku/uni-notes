# 11. 🧾 8086 Assembly Example

**Source slides:** 127--128.

## Core idea

The final slides show how the abstract ideas become an actual
assembly-language program.

The example defines two data values, adds them, stores the result, and
then invokes an interrupt instruction.

## Source program

``` asm
DATA SEGMENT
N1 DB 12H
N2 DB 21H
RES DB ?
DATA ENDS

CODE SEGMENT
ASSUME CS:CODE, DS:DATA

START:
    MOV AX, DATA
    MOV DS, AX
    MOV AL, N1
    MOV BL, N2
    ADD AL, BL
    MOV RES, AL
    INT 21H

CODE ENDS
END START
```

## Understand the flow

### 1. Define data

``` asm
N1 DB 12H
N2 DB 21H
RES DB ?
```

The source uses: - `N1` = `12H` - `N2` = `21H` - `RES` = uninitialized
result location

### 2. Initialize the data segment

``` asm
MOV AX, DATA
MOV DS, AX
```

The program establishes the data-segment register.

### 3. Load operands

``` asm
MOV AL, N1
MOV BL, N2
```

Now the operands are in CPU registers.

### 4. Execute the arithmetic

``` asm
ADD AL, BL
```

The ALU performs the addition.

Since:

$$
12_H + 21_H = 33_H
$$

the result is:

``` text
AL = 33H
```

### 5. Store the result

``` asm
MOV RES, AL
```

The result moves from the register back to memory.

``` mermaid
flowchart LR
    N1[Memory: N1=12H] --> AL[AL]
    N2[Memory: N2=21H] --> BL[BL]
    AL --> ADD[ALU: ADD]
    BL --> ADD
    ADD --> AL2[AL=33H]
    AL2 --> RES[Memory: RES]
```

### 6. End/control transfer

The source uses:

``` asm
INT 21H
```

The notes do not provide a detailed explanation of the interrupt
mechanism here, so **do not infer more from this slide than the
instruction's presence**.

## Connection to earlier topics

This tiny program demonstrates several Unit 2 concepts simultaneously:

  Earlier concept          Assembly example
  ------------------------ -------------------------------
  Data transfer            `MOV`
  Registers                `AL`, `BL`, `AX`, `DS`
  Arithmetic               `ADD`
  Memory                   `N1`, `N2`, `RES`
  Segmentation             `DATA SEGMENT`, `DS`
  Instruction sequencing   Instructions execute in order

That is why the 8086 case study comes at the end: it gives a concrete
form to concepts introduced earlier.

## What to remember

### Must understand

The data flow:

``` text
memory → registers → ALU → register → memory
```

### Must remember

The source example's important instructions: - `MOV` → copy/transfer -
`ADD` → addition - `INT 21H` appears as the final control instruction in
the example

### Low priority

Memorizing the entire program character-for-character. Understand the
flow first.

## Quick check

1.  Why are `N1` and `N2` loaded into registers before `ADD`?
2.  Where is the result after `ADD AL, BL`?
3.  Why is `MOV RES, AL` needed after the addition?
