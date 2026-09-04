# 5. 🔢 Endianness and Alignment

**Source slides:** 49--54.

## Core idea

When a multi-byte value is stored in memory, **endianness** determines
which byte goes at the lowest memory address.

This matters when the same binary data is interpreted or transferred
between systems.

## Big-endian vs little-endian

### Big-endian

The **most significant byte** is stored at the **lowest address**.

``` text
Low address
   ↓
+----+----+----+----+
| MSB|    |    | LSB|
+----+----+----+----+
```

### Little-endian

The **least significant byte** is stored at the **lowest address**.

``` text
Low address
   ↓
+----+----+----+----+
| LSB|    |    | MSB|
+----+----+----+----+
```

## A reliable way to reason about it

Do not memorize the names separately.

Remember **"lowest address"** and ask:

> Which end of the value goes there?

-   **Big end → low address**
-   **Little end → low address**

## Alignment

A word is **aligned** when it starts at an address appropriate to its
size.

The source gives:

  Data size   Aligned starting addresses
  ----------- ----------------------------
  16-bit      `0, 2, 4, ...`
  32-bit      `0, 4, 8, ...`
  64-bit      `0, 8, 16, ...`

If a word begins at an arbitrary byte address, the source calls it
**unaligned**.

### Pattern

The alignment step equals the number of bytes in the word.

For an $n$-byte word:

$$
\text{aligned starts} = 0,n,2n,3n,\ldots
$$

## What to remember

### Must understand

-   Endianness concerns **byte order within a multi-byte word**.
-   Big-endian → most significant byte at lowest address.
-   Little-endian → least significant byte at lowest address.
-   Alignment means starting at an address consistent with the word
    size.

### Must remember

-   16-bit → step 2
-   32-bit → step 4
-   64-bit → step 8

### Common trap

**Endianness is not about the order of bits inside a byte.** The source
is discussing the ordering of **bytes**.

## Quick check

1.  A 32-bit value has four bytes. In little-endian order, which byte
    goes at the lowest address?
2.  Is address 6 aligned for a 32-bit word according to the source's
    alignment pattern?
3.  What is the difference between an endian problem and an alignment
    problem?
