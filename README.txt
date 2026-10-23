 _               
(_)_   _____ ___ 
| \ \ / / __/ __|
| |\ V / (_| (__ 
|_| \_/ \___\___|

Ivan's C compiler toolchain!

SYNOPSIS

    ivcc is a C99 compiler toolchain for the x86-64 architecture. It includes
    a preprocessor, compiler, assembler, archiver, linker, emulator, and its
    own C standard library and math library.

        ivcc  - Compiler driver
        ivas  - AT&T syntax assembler
        ivar  - Static library archiver
        ivld  - ELF linker
        ivemu - Emulator and disassembler

    The default target is x86-64 Linux. The compiler can write preprocessed
    source, assembly, ELF relocatable objects, or static executables. See
    CHECKLIST for the detailed language and standard library feature list.

BUILDING

    Build on x86-64 Linux with GCC, GNU make, Flex, and Bison installed:

        make

    The build uses GCC for the tools, then ivcc and ivar for the bundled
    runtime libraries. The resulting files are placed in:

        build/                  # Directory: For build
        ├── bin/                # Directory: For tools
        │   ├── ivar            # Tool: Archiver
        │   ├── ivas            # Tool: Assembler
        │   ├── ivcc            # Tool: Compiler driver
        │   ├── ivemu           # Tool: Emulator
        │   └── ivld            # Tool: Linker
        ├── include/            # Directory: C and math library headers
        └── lib/                # Directory: For libraries
            └── x86_64/         # Directory: For x86-64 architecture
                ├── ivemu/      # Directory: Runtime for ivemu
                │   └── crt0.o  # Emulator startup object
                └── linux/      # Directory: Runtime for linux
                    ├── crt0.o  # Linux startup object
                    ├── libc.a  # C standard library
                    └── libm.a  # Math library

    From the project root, add the tools to PATH for this shell session:

        export PATH="$PWD/build/bin:$PATH"

    The examples below assume this PATH setting and run from the project
    root.

    The compiler finds the headers and runtime files relative to its own
    executable. Keep the build/bin, build/include, and build/lib layout
    together when moving the toolchain. There is no make install target.

    To remove the build output:

        make clean

QUICK START

    Save this program as hello.c:

        #include <stdio.h>

        int main(void)
        {
            puts("Hello from ivcc!");
            return 0;
        }

    Compile with Ivan's compiler ivcc:

        $ ivcc hello.c -o hello

    Run with Ivan's emulator ivemu, or run directly:

        $ ivemu ./hello
        $ ./hello

    Both commands print:

        Hello from ivcc!

COMPILING AND LINKING

    ivcc accepts one C source file per invocation. Without -o, an executable
    is written to a.out, assembly to INPUT.s, and an object to INPUT.o.
    Preprocessed source is written to standard output.

        $ ivcc -E hello.c
        $ ivcc -S hello.c -o hello.s
        $ ivas hello.s -o hello.o

    To build a program from several source files, compile each separately
    and pass the objects and runtime files to ivld:

        $ ivcc -c main.c -o main.o
        $ ivcc -c helper.c -o helper.o
        $ ivld -o app main.o helper.o \
            build/lib/x86_64/linux/crt0.o \
            build/lib/x86_64/linux/libc.a

    ivcc links the Linux startup object and libc automatically when writing
    an executable. Add -lm for programs that use the math library:

        $ ivcc math_example.c -lm -o math_example

    When linking with ivld directly, supply libm.a before libc.a. Archives
    are searched for symbols needed by the inputs that precede them.

    To create and inspect a static library:

        $ ivar rcs libhelper.a helper.o
        $ ivar t libhelper.a

    Pass an archive to ivld after the objects that use its symbols.

    The multi-file and archive examples use this layout:

        ./               # Example project
        ├── app          # Linked executable
        ├── helper.c     # Helper source
        ├── helper.o     # Compiled helper object
        ├── libhelper.a  # Archive containing helper.o
        ├── main.c       # Program source
        └── main.o       # Compiled program object

COMPILER OPTIONS

        -E                  Preprocess only
        -P                  Omit line markers from preprocessed output
        -S                  Write assembly text
        -c                  Write a relocatable object
        -o FILE             Set the output file; - means standard output
        -I DIR              Add an include directory
        -D NAME[=VALUE]     Define a macro; the default value is 1
        -U NAME             Undefine a macro
        --include=FILE      Include FILE before the input source
        --std=c99           Select the supported language standard
        -march=x86_64       Select the supported architecture
        -mtarget=linux      Select the default Linux runtime
        -mtarget=ivemu      Select the minimal emulator runtime
        -lNAME              Link libNAME.a from the runtime directory
        -B DIR              Override the runtime directory
        --M / --MM          Write make dependencies instead of compiling
        --MD / --MMD        Write dependencies alongside compilation
        --MF=FILE           Set the dependency output file
        --MT=TARGET         Set the dependency rule's target
        --MQ=TARGET         Set and escape the dependency rule's target
        --MP                Add empty rules for included headers

    --MM and --MMD omit system headers. Dependency options use two leading
    dashes. Some GCC compatibility options, including -O, -g, and -L, are
    accepted but ignored; they do not enable optimization, debug information,
    or extra library search paths.

EMULATOR

    ivemu loads x86-64 ELF executables and implements the Linux system calls
    used by the bundled runtime. It also provides inspection and tracing:

        $ ivemu -i ./hello    # Show the loaded image
        $ ivemu -d ./hello    # Disassemble
        $ ivemu -t ./hello    # Trace instructions to standard error

    The Linux target supports the bundled libc and libm under ivemu. The
    separate -mtarget=ivemu target supplies only a minimal startup object
    that calls main and halts with its return status; it does not link libc
    automatically. For example:

        ivcc -mtarget=ivemu tests/lang/lang001_return.c -o return-test
        ivemu ./return-test
        echo $?                     # 200, the test program's return value

TESTING

    Run the test suite from the project root:

        make tests

    The test runner also requires GNU binutils (ar and the linker used by
    GCC), timeout, and standard shell utilities. Tests check compilation,
    diagnostics, output, and exit status through five pipelines: direct
    compilation, assembly, archiving, linking, and emulation. The archiver
    pipeline compares its output with a deterministic GNU ar archive.

    Run a group or an individual test:

        make test_lang
        make test_bugs
        make test_edge
        make test_libc
        make test_libm
        make test_errs
        make test_arch
        make lang/lang011_call

    After building, a test can also be run directly:

        $ tests/run_test tests/lang/lang011_call.c

ARCHITECTURE

        ./                     # Project root
        ├── h/                 # Header files
        │   ├── arch/          # Compiler backend
        │   │   └── x86_64/    # Architecture: x86-64
        │   │       ├── asm.h  # Module: Asm IR
        │   │       ├── cpu.h  # Module: CPU
        │   │       ├── enc.h  # Module: Encoder
        │   │       ├── gen.h  # Module: Codegen 
        │   │       └── txt.h  # Module: Assembly text
        │   ├── lang/          # Compiler frontend
        │   │   ├── ast.h      # Module: AST
        │   │   ├── par.h      # Module: Parser
        │   │   ├── pp.h       # Module: Preprocessor
        │   │   └── sem.h      # Module: Semantica analyzer
        │   ├── libc/          # Standard C library (runtime)
        │   ├── libm/          # Standard Math library (runtime)
        │   ├── util/          # Utilities
        │   │   ├── console/   # Utilities: Console
        │   │   └── object/    # Utilities: Objects and archives
        │   ├── ar.h           # Tool: Archiver
        │   ├── as.h           # Tool: Assembler
        │   ├── cc.h           # Tool: Compiler driver
        │   ├── emu.h          # Tool: Emulator
        │   └── ld.h           # Tool: Linker
        ├── src/               # Source files (mirrors h/)
        ├── tests/             # Myriad tests
        └── CHECKLIST          # ISO C99 compliance checklists

LICENSE

    ivcc is distributed under the GNU General Public License, version 3 or
    later. See LICENSE for the full text.

    Runtime files bearing the corresponding notice also carry the GCC
    Runtime Library Exception, version 3.1. See COPYING.RUNTIME for its terms.

CONTRIBUTING

    ivcc project is not open to contributions.

AUTHOR

    Copyright (C) Ivan Janevski 2026


