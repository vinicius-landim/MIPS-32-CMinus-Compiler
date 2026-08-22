# C- Compiler

Complete compiler for the **C-** language (a C subset described by Louden, 2004), with a backend for a single-cycle 32-bit MIPS processor developed in the Computer Systems Laboratory course at UNIFESP.

The compiler translates a C-- source program into executable binary code for the target processor, going through the phases of lexical, syntactic, and semantic analysis, intermediate code generation (quadruples), assembly code generation, and binary translation.

---

## Project structure

```
/
├── src/          Compiler source code
├── tests/        C-- test programs
└── docs/         Project technical report
```

### Modules in `/src`

| File | Description |
|---|---|
| `globals.h` | Shared global definitions across modules (AST, tokens, types) |
| `scanner.l` | Lexical analyzer (Flex) |
| `parser.y` | LALR syntactic analyzer (Bison) — builds the AST |
| `util.h / util.c` | Utility functions for AST node creation and printing |
| `symtab.h / symtab.c` | Symbol table with scope stack |
| `analyze.h / analyze.c` | Semantic analysis: table construction and type checking |
| `cgen.h / cgen.c` | Intermediate code generation (quadruples) |
| `assembly.h / assembly.c` | Assembly code generation |
| `binary.h / binary.c` | Translation to 32-bit binary code |
| `main.c` | Entry point — orchestrates all phases |

---

## Dependencies

- **GCC**
- **Flex** — lexical analyzer generator
- **Bison** — syntactic analyzer generator

On Ubuntu/Debian:

```bash
sudo apt install gcc flex bison
```

---

## Compilation

```bash
cd src

# Generate the scanner and parser
flex scanner.l
bison -d parser.y

# Compile
gcc -o compiler lex.yy.c parser.tab.c main.c util.c symtab.c analyze.c cgen.c assembly.c binary.c
```

---

## Usage

```bash
./compiler <file.cm>
```

Before running, create the output folder:

```bash
mkdir -p output_files
```

### Outputs generated in `output_files/`

| File | Content |
|---|---|
| `tabela_simbolos.txt` | Symbol table with scopes, types, and line numbers of usage |
| `codigo_intermediario.txt` | Sequence of generated quadruples |
| `codigo_assembly.txt` | Assembly code for the target processor |
| `codigo_binario.txt` | 32-bit binary code, one instruction per line |
| `arvore.dot` | AST in Graphviz format |

### Example

```bash
./compiler ../tests/fact.cm
```

To visualize the AST:

```bash
dot -Tpng output_files/arvore.dot -o output_files/arvore.png
```

---

## Test programs

The programs in `/tests` cover the main features of the language:

| File | Description |
|---|---|
| `fact.cm` | Factorial calculation — recursion, context saving |
| `gcd.cm` | Greatest common divisor — recursion with multiple parameters |
| `sort.cm` | Selection sort — global arrays, multiple functions |

---

## Target architecture

The compiler generates code for a single-cycle 32-bit MIPS processor with Harvard architecture:

- Separate instruction and data memory
- Data memory: 1024 × 32 bits (4 KB)
- 32-bit instructions in R, I, and J formats
- Global data allocated from the base (`0x000`)
- Stack growing from the top (`0x3FF`) towards the base

---

## Reference

LOUDEN, Kenneth C. **Compiladores: princípios e práticas** (Compiler Construction: Principles and Practice). São Paulo: Pioneira Thomson Learning, 2004.
