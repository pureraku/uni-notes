---
title: COA Unit 2 --- Study Notes
---

# 🧠 COA Unit 2 --- Study Notes

> **Source:** `notes.pdf` --- Computer Organization and Architecture,
> Unit 2: *Basic Structure of a Computer*.
>
> These notes reorganize the source slides for **deep understanding**,
> while preserving the source terminology and examples. They do not
> silently add outside material.

## Table of contents

1.  [Basic structure](01_basic_structure.md)
2.  [CPU, registers and control](02_cpu_registers_control.md)
3.  [Bus structures](03_bus_structures.md)
4.  [Memory organization](04_memory_organization.md)
5.  [Endianness and alignment](05_endianness_alignment.md)
6.  [Instructions, RTN and instruction
    formats](06_instructions_and_formats.md)
7.  [Instruction cycle, sequencing and condition
    codes](07_instruction_cycle_and_sequencing.md)
8.  [Addressing modes](08_addressing_modes.md)
9.  [Microprocessors](09_microprocessors.md)
10. [8086 architecture and registers](10_8086.md)
11. [8086 assembly example](11_8086_assembly.md)
12. [Study checklist](12_study_checklist.md)

## Dependency map

``` mermaid
flowchart TD
    A[Basic computer structure] --> B[CPU + registers + control]
    B --> C[Bus communication]
    C --> D[Memory + addresses]
    D --> E[Endianness + alignment]
    B --> F[Instructions + RTN]
    F --> G[Instruction formats]
    G --> H[Instruction cycle]
    H --> I[Sequencing + condition codes]
    G --> J[Addressing modes]
    B --> K[Microprocessor]
    K --> L[8086 architecture]
    L --> M[8086 registers]
    M --> N[Assembly example]
```

## How to use these notes

-   [ ] First pass: understand the diagrams and cause → effect
    relationships.
-   [ ] Second pass: solve the **Quick checks** without looking back.
-   [ ] Third pass: use the **Must remember** boxes for exam revision.
-   [ ] Leave **Low priority** details until the end.

### Rendering

The notes use ordinary Markdown plus optional: - **KaTeX** math: `$...$`
and `$$...$$` - **Mermaid** diagrams - **PlantUML** blocks - **Graphviz
DOT** blocks - task lists - relative local images

They are written with relative paths so the folder works across **macOS
/ Linux / Windows**.
