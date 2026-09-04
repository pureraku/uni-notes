# 12. ✅ Study Checklist

Use this only after reading the section notes.

## Tier 1 --- Must understand

-   [ ] I can explain the four basic computer functions.
-   [ ] I can explain the roles of ALU, Control Unit, registers, memory
    and buses.
-   [ ] I can distinguish **WHAT** the instruction specifies from
    **WHEN** the Control Unit makes actions happen.
-   [ ] I can distinguish PC from IR.
-   [ ] I can distinguish MAR from MDR.
-   [ ] I can explain address bus vs data bus vs control bus.
-   [ ] I can derive the number of address bits using $2^x=n$.
-   [ ] I can explain load vs store.
-   [ ] I can explain big-endian vs little-endian without memorizing a
    picture.
-   [ ] I can explain the four instruction-cycle steps.
-   [ ] I can explain why a loop changes the normal PC sequence.
-   [ ] I can distinguish direct, indirect, register direct and register
    indirect addressing.
-   [ ] I can derive indexed/relative effective-address formulas.
-   [ ] I can explain why auto-increment and auto-decrement differ.
-   [ ] I can explain the purpose of condition codes.
-   [ ] I can connect the general architecture to the 8086 example.

## Tier 2 --- Must remember

-   [ ] `CPU = ALU + Control Unit + Registers`
-   [ ] `2^x = n`
-   [ ] `EA = A` --- direct
-   [ ] `EA = [A]` --- indirect
-   [ ] `EA = A + [Index]` --- indexed
-   [ ] `EA = PC + A` --- relative
-   [ ] `N, Z, V, C` --- condition codes
-   [ ] 8086: 16-bit, 20 address lines, 16 data lines, 1 MB (source)
-   [ ] 8086 instruction queue: 6 bytes
-   [ ] 8086 pipeline stages: Fetch + Execute

## Tier 3 --- Low priority

-   [ ] Detailed computer-type classifications
-   [ ] Historical microprocessor lists/dates
-   [ ] Long lists of instruction mnemonics
-   [ ] Exact wording of the 8086 register descriptions

## High-value self-test

### 1. Addressing

If an instruction contains `A`, memory location `A` contains `500`, and
memory location `500` contains `42`, what does each of these mean?

``` text
Immediate
Direct
Indirect
```

### 2. CPU flow

Explain this without notes:

``` text
PC → Memory → IR → Decode → Operand access → ALU/other execution → Result
```

### 3. Memory

A machine has $2^{28}$ bytes of byte-addressable memory.

How many address bits are required?

### 4. Instruction formats

Why can a three-address instruction reduce program length but still fail
to make execution faster?

### 5. Registers

Explain the difference between:

``` text
PC
IR
MAR
MDR
```

in one sentence each.

### 6. 8086

Explain how the 8086 case study connects: - segments, - registers, -
instruction queue, - buses, - ALU, - flags.

If you can explain those connections rather than merely list them, you
understand the unit.
