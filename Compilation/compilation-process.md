# Big picture (one-line)
Source code → preprocessing → lexing/tokenizing → parsing → semantic analysis & type checking → IR generation → optimizations → code generation (assembly) → assembler (.o) → linker → executable (→ loader/runtime).

# Preprocessing
**What it does :**
- Handles `#include`, `#define macros`, conditional compilation `#if/#ifdef`.
- Produces a translation unit (single big source text) fed to the lexer.
```bash
gcc -E main.c -o main.i   # or g++ -E for C++
```

# Lexical analysis (tokenization)
**What it does :**
- Converts preprocessed source characters into tokens: identifiers, keywords, literals, operators, punctuators.
- Detects simple lexing errors (unterminated string, invalid numeric literal).

**Example:**
- Source: `int x = 42;`
- Tokens: `int identifier(x) = numeric-literal(42) ;`

# Parsing → AST (Abstract Syntax Tree)
**What it does :**
- Consumes tokens according to grammar, produces a parse tree / AST.
- In C++ this is complex (templates, elaborate grammar, ambiguity resolution).

**Example :** 
- parsing `int f(int a){ return a+1; }` → AST node `FunctionDecl(f)` with parameter and `ReturnStmt(BinaryOp(+, a, 1))`.

# Semantic analysis & name resolution
**What it does :**
- Builds symbol table, resolves identifiers to declarations, performs type checking, checks scoping rules.
- In C++: overload resolution, template instantiation, name mangling, conversion rules, access control (private/protected), ADL (argument-dependent lookup).
- Reports errors/warnings.

**Examples of semantic checks :**
- Type mismatch: `int x = "hello"`; → error.
- Use-before-declaration when not allowed.
- For C++: choose which overload of `f()` to call; instantiate template `vector<int>`.

# Intermediate representation (IR) generation / translation
**What it does :**
- Translates AST into an intermediate form that’s easier for analyses and optimizations.
- Classic compilers: generate an IR per function (e.g., LLVM IR, GCC GIMPLE/RTL).

**Why IR?**
- Easier to implement language-independent optimizations.
- IR often uses a form like three-address code or SSA (Static Single Assignment).

Simple IR example (pseudo-IR) for int add(int a,int b){return a+b;}:
```bash
t1 = a + b
return t1
```

# Optimizations (middle-end)

**What it does :**
- Transform IR to make code smaller/faster. Two broad classes:
  - Local (within a basic block): constant folding, algebraic simplification.
  - Global: inlining, common subexpression elimination (CSE), dead-code elimination (DCE), loop-invariant code motion, loop unrolling.
- Register allocation (back-end) — mapping virtual registers to physical registers (graph coloring, linear scan).
- Many modern compilers convert IR to SSA for easier optimization.

**Examples**
- Constant folding: `x = 2 + 3 → x = 5.`
- Inlining: call to small function replaced by body (saves call overhead).
- Dead code elimination: remove if(false) foo();.

Tip: inspect optimizations by compiling with optimization flags:
```bash
gcc -O0 -S file.c      # no optimization -> assembly
gcc -O2 -S file.c      # optimized assembly
```

# Code generation (lowering to assembly / machine code)

**What it does**
- Convert optimized IR into target-specific assembly: emit instructions, choose calling convention, generate prolog/epilog, handle stack frame.
- Produce relocatable code with references to symbols that may be resolved at link time.

# Assembler → object file (.o)
**What it does**
- Assembler turns assembly into object file format (ELF on Linux, Mach-O on macOS, PE on Windows).
- Object file sections: .text (code), .data (initialized data), .rodata (read-only data), .bss (zero-initialized).
- Includes symbol table and relocation entries for unresolved external symbols.

# Linker
**What it does**
- Combines object files and libraries into an executable or shared library.
- Symbol resolution: match symbol references (undefined) to symbol definitions.
- Relocation: fixup addresses (patch code/data with final addresses).
- Handles static linking (copy code into executable) or dynamic linking (reference shared libs using PLT/GOT).
- Produces final executable image with metadata (entry point, program headers).

Two-stage conceptual link operations
- Resolve symbols: find definitions for all undefined references (from other object files or libraries).
- Perform relocations: adjust code/data to final addresses.
