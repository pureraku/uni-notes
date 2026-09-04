# 8. 🎯 Addressing Modes

**Source slides:** 84--103.

## Core idea

An **addressing mode** tells the processor **how to locate an operand**.

The source gives two purposes:

1.  Programming versatility.
2.  Reducing the number of bits needed in the instruction's addressing
    field.

## The master question

For every addressing mode, ask:

> **Where is the operand, and how many steps are needed to find it?**

## Summary table

  -----------------------------------------------------------------------
  Mode                    Where is the            Effective address
                          operand/address?        
  ----------------------- ----------------------- -----------------------
  **Immediate**           Inside instruction      Operand is directly
                                                  available

  **Direct**              Address field gives     $EA=A$
                          operand address         

  **Indirect**            Memory at `A` contains  $EA=[A]$
                          operand address         

  **Register direct**     Operand is in a CPU     Register contents
                          register                

  **Register indirect**   Register contains       $EA=[R]$
                          operand address         

  **Indexed**             Address field + index   $EA=A+[Index]$
                          register                

  **Relative**            Address field + PC      $EA=PC+A$

  **Auto-increment**      Register gives operand  $EA=R$
                          address, then register  
                          increments              

  **Auto-decrement**      Register decrements     $EA=R-d$
                          first, then gives       
                          operand address         
  -----------------------------------------------------------------------

## 8.1 Immediate addressing

The operand is explicitly contained in the instruction.

Example:

``` text
ADD 5
```

Conceptually:

$$
AC \leftarrow AC+5
$$

**Key properties from the source:** - No memory reference is needed to
fetch the operand. - Fast. - Limited range.

### Mental model

``` text
Instruction → operand
```

## 8.2 Direct addressing

The instruction contains the operand's memory address.

$$
EA=A
$$

Example:

``` text
ADD A
```

means:

> Find the operand directly at memory location `A`.

Only one memory reference is needed to obtain the operand.

### Mental model

``` text
Instruction → address → operand
```

## 8.3 Indirect addressing

The instruction points to a memory location that contains the **address
of the operand**.

$$
EA=[A]
$$

This requires two memory references:

``` text
A → address of operand → operand
```

### Why it costs more

The CPU cannot get the operand immediately because it first has to
retrieve the operand's address.

## 8.4 Register direct addressing

The operand is in a CPU register.

No memory access is needed for the operand.

Example:

``` text
ADD R
```

The source gives:

$$
AC \leftarrow AC+[R]
$$

### Why it is fast

Registers are inside the processor and are very small/limited, so the
address field can also be small.

## 8.5 Register indirect addressing

The instruction identifies a register, but the register contains the
**effective address** of the operand.

$$
EA=[R]
$$

The source example:

$$
AC \leftarrow AC+[[R]]
$$

The double bracket expresses the extra level of indirection:

``` text
R → memory address → operand
```

### Common confusion

**Register direct:** register contains the **data**.

**Register indirect:** register contains the **address of the data**.

## 8.6 Indexed addressing

The effective address is formed by adding:

-   address part of instruction
-   contents of index register

$$
EA=A+[Index]
$$

## 8.7 Relative addressing

A version of displacement addressing.

The source gives:

$$
EA=PC+A
$$

The important idea is:

> The target is specified relative to the current program-counter
> position.

## 8.8 Auto-increment

A special case of register indirect addressing.

First use the register as the operand address:

$$
EA=R
$$

Then increment the register:

$$
R\leftarrow R+d
$$

where `d` depends on the operand size.

### Sequence

``` text
use R
  ↓
read operand
  ↓
R = R + d
```

## 8.9 Auto-decrement

The order is reversed.

First decrement:

$$
R\leftarrow R-d
$$

then use the new value to locate the operand.

So:

$$
EA=R-d
$$

### Sequence

``` text
R = R - d
  ↓
use R
  ↓
read operand
```

## The important comparison

``` mermaid
flowchart TD
    A[Addressing mode] --> B{Where is the useful information?}
    B --> C[Operand in instruction]
    B --> D[Address in instruction]
    B --> E[Address in register]
    B --> F[Address formed from PC/index]
    C --> C1[Immediate]
    D --> D1[Direct]
    D --> D2[Indirect: memory holds address]
    E --> E1[Register direct: register holds data]
    E --> E2[Register indirect: register holds address]
    F --> F1[Relative: PC + displacement]
    F --> F2[Indexed: index + address field]
```

## What to remember

### Must understand

The difference between: - immediate vs direct - direct vs indirect -
register direct vs register indirect - indexed vs relative -
auto-increment vs auto-decrement

### Must remember

$$
EA=A \quad\text{(direct)}
$$

$$
EA=[A] \quad\text{(indirect)}
$$

$$
EA=A+[Index] \quad\text{(indexed)}
$$

$$
EA=PC+A \quad\text{(relative)}
$$

$$
EA=R \quad\text{then }R\leftarrow R+d\quad\text{(auto-increment)}
$$

$$
R\leftarrow R-d\quad\text{then use }R\quad\text{(auto-decrement)}
$$

### Common traps

-   **Direct ≠ register direct.** Direct uses a memory address; register
    direct uses a CPU register.
-   **Register indirect does not mean "data is in the register."** The
    register contains an address.
-   **Auto-increment and auto-decrement differ in order.**

## Quick check

1.  If an instruction contains the value `25`, which addressing mode is
    that?
2.  If `R1` contains `500`, and the operand is stored at memory location
    `500`, which mode uses `R1` as the pointer?
3.  Which happens first in auto-decrement: memory access or register
    decrement?
