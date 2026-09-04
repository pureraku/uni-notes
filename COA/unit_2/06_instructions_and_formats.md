# 6. 🧩 Instructions, RTN and Instruction Formats

**Source slides:** 55--74.

## Core idea

An **instruction** tells the processor what task to perform on specified
data.

An **instruction set** is the complete group of instructions supported
by the processor.

Instruction sequencing is the order in which program instructions
execute.

## Four broad instruction operations

The source says a computer needs instructions capable of:

1.  Data transfer between memory and processor registers
2.  Arithmetic and logic operations
3.  Program sequencing and control
4.  I/O transfer

## Register Transfer Notation (RTN)

RTN describes transfers between registers, memory and I/O.

The source conventions:

-   `LOC`, `PLACE`, `MEM` → memory locations
-   `R1`, `R2`, ... → processor registers
-   `DATA_IN`, `DATA_OUT` → I/O registers
-   `[X]` → contents of `X`
-   RHS → **source/value**
-   LHS → **destination**
-   Source is not modified.
-   Destination is overwritten.

### Example

``` text
R2 ← [LOCN]
```

means:

> Put the contents of memory location `LOCN` into `R2`.

Another example:

``` text
R4 ← [R3] + [R2]
```

means:

> Read the contents of `R3` and `R2`, add them, and place the result in
> `R4`.

## Data transfer instructions

The source calls these **copy instructions**.

Examples listed: - `MOV` - `LDA` - `STA` - `PUSH` - `POP`

## Data manipulation instructions

Three categories:

1.  **Arithmetic**
2.  **Logical and bit manipulation**
3.  **Shift**

Examples from the source:

### Arithmetic

-   `INC`
-   `DEC`
-   `ADD`
-   `ADC`
-   `MUL`

### Logical/bit manipulation

-   `AND`
-   `OR`
-   `NOT`
-   `XOR`

### Shift/rotate

-   `SHR`
-   `ROL`
-   `RCL`

## Instruction fields

The source divides an instruction into fields.

  Field                 Meaning
  --------------------- ---------------------------
  **Operation field**   What operation to perform
  **Address field**     Location of the operand
  **Mode field**        How to find the operand

``` text
Instruction
┌────────────┬──────────────┬────────────┐
│ Operation  │ Address(es)  │ Mode       │
└────────────┴──────────────┴────────────┘
     WHAT          WHERE        HOW
```

## Number of address fields

The source classifies instructions as:

-   **Zero-address**
-   **One-address**
-   **Two-address**
-   **Three-address**

The number of address fields affects how much operand information is
explicitly present in an instruction.

## Zero-address instructions

Used in stack-based computers.

Operands are implicit because they are taken from the **pushdown
stack**.

Example from the source: evaluate

$$
(A+B)(C+D)
$$

``` text
PUSH A
PUSH B
ADD
PUSH C
PUSH D
ADD
MUL
POP X
```

The `ADD` instruction does not say "use A and B." The stack determines
which operands it uses.

``` mermaid
flowchart TD
    A[PUSH A] --> B[PUSH B]
    B --> C[ADD → A+B]
    C --> D[PUSH C]
    D --> E[PUSH D]
    E --> F[ADD → C+D]
    F --> G[MUL → (A+B)(C+D)]
    G --> H[POP X]
```

## One-address instructions

One operand is explicitly named; the other is implicitly the
**accumulator (AC)**.

For example:

``` text
ADD B
```

means conceptually:

$$
AC \leftarrow AC + M[B]
$$

## Two-address instructions

Syntax in the source:

``` text
Operation source, destination
```

Example for $(A+B)(C+D)$:

``` text
MOV R1,A
ADD R1,B
MOV R2,C
ADD R2,D
MUL R1,R2
MOV X,R1
```

## Three-address instructions

Syntax:

``` text
Operation source1, source2, destination
```

Example:

``` text
ADD R1,A,B
```

means:

$$
R1 \leftarrow M[A]+M[B]
$$

The source notes the main trade-off:

-   **Advantage:** shorter programs / easier program creation.
-   **Disadvantage:** instruction encoding can become large because more
    address fields are required.
-   A shorter program does **not necessarily mean faster execution**.

![Three-address example from the
source](assets/three-address-example.png)

## The big pattern

``` text
0-address → operands mostly implicit
1-address → accumulator implied
2-address → two explicit operands/roles
3-address → two sources + destination
```

## What to remember

### Must understand

-   RTN source vs destination.
-   Instruction fields: operation, address, mode.
-   Zero/one/two/three address is about the number of explicit address
    fields.
-   More explicit operands can reduce the number of instructions needed,
    but may increase instruction size.

### Quick check

1.  In `R2 ← [LOCN]`, which side is the source?
2.  Why can `ADD` have no operand fields in a zero-address instruction?
3.  Why can a three-address instruction make a program shorter without
    necessarily making execution faster?
