# 📚 COA Unit 2 Markdown Notes

These files are a study-oriented rewrite of the supplied `notes.pdf`.

## Files

-   `00_index.md` --- navigation + dependency map
-   `01_basic_structure.md` --- computer functions and functional units
-   `02_cpu_registers_control.md` --- CPU and registers
-   `03_bus_structures.md` --- buses and bus structures
-   `04_memory_organization.md` --- memory, address space, load/store
-   `05_endianness_alignment.md` --- byte ordering and alignment
-   `06_instructions_and_formats.md` --- instructions, RTN,
    0/1/2/3-address formats
-   `07_instruction_cycle_and_sequencing.md` --- fetch/decode/execute,
    sequencing, flags
-   `08_addressing_modes.md` --- all addressing modes in the source
-   `09_microprocessors.md` --- microprocessor/microcontroller and
    evolution
-   `10_8086.md` --- 8086 architecture and registers
-   `11_8086_assembly.md` --- source assembly example
-   `12_study_checklist.md` --- active-recall checklist
-   `assets/` --- local images rendered from source slides

## Markdown features used

-   Table of contents
-   Mermaid
-   PlantUML
-   KaTeX-compatible math
-   Graph/flow diagrams
-   Task lists
-   Emojis
-   Local images
-   Relative links for cross-platform use

## Cross-platform use

Keep the folder structure intact:

``` text
coa_unit2_notes/
├── *.md
└── assets/
    └── *.png
```

Because links are relative, the notes can be moved between **macOS,
Linux, and Windows** without changing paths.

## Source handling

Where the source is ambiguous or uses a context-dependent statement, the
notes explicitly flag it rather than silently replacing it with outside
knowledge.

Examples: - PC increment: one slide says `+1`, while another example
uses `+4` because it assumes 4-byte instructions. - The 8086 slide
states a 1976 design date; the notes preserve that as a source
statement. - The final assembly slide contains `INT 21H` but does not
explain its mechanism in detail, so the notes do not invent an
explanation.
