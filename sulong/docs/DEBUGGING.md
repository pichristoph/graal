# Source-Level Debugging

Sulong supports source-level debugging on the
[Chrome Developer Tools](https://developers.google.com/web/tools/chrome-devtools/) using GraalVM's
Chrome Inspector. This includes support for single-stepping, breakpoints and inspection of local
and global variables.

## Prerequisites

Sulong supports IR-level debugging, as well as source-level debugging. Concerning source-level debugging, it is important that the LLVM bitcode file has been compiled by clang using the `-g` option in order to provide source-level information for the debugger. If source-level debugging is not used (only IR-level debugging), then this `-g` option is not necessary. 

## Setup

The Chrome Inspector can be used with both the precompiled GraalVM and Sulong built from source.

### GraalVM

The easiest way to use Sulong's source-level debugging capabilities is to run it from GraalVM.
To start debugging simply run the following in GraalVM's `bin` directory:

    lli --inspect --llvm.enableLVI <bitcode file>

### Built from source

The source code of Chrome Inspector is available as part of the
[Tools suite in the Graal repository](https://github.com/oracle/graal/tree/master/tools).
If you followed the instructions in [Sulong's README](../README.md) and already built Sulong the Tools suite
should be available at `sulong-dev/graal/tools`.
You can use following command from the `sulong-dev/graal/sulong` directory to build the Tools suite.

     mx --dynamicimports /tools build

See the [build instructions in Tools's README](https://github.com/oracle/graal/blob/master/tools/README.md)
for more information.

To debug a program you can then use the following command in `sulong-dev/graal/sulong`:

    mx --dynamicimports /tools lli --inspect --llvm.enableLVI <bitcode file>

This can also be used in conjunction with the `-d` option to `mx`, allowing you to attach a Java
Debugger for debugging Sulong itself in addition to the source-level debugger.

## Usage

When launched, the inspector will suspend execution at the first instruction of the program and print
a link to the console. Pasting this link into Chrome's address bar will open the developer tools for you.

### Breakpoints

Breakpoints can only be set in functions that have already been parsed. Sulong defaults to parsing
functions in LLVM bitcode files only when they are first being executed. To instead parse functions
eagerly and be able to set breakpoints also in functions not yet executed you can launch Sulong
with the option `--llvm.lazyParsing=false`.

### Program-defined breakpoints using `__builtin_debugtrap()`

The `__builtin_debugtrap` function enables you to mark locations in your program at which you explicitly
want Sulong to halt the program and switch to the debugger. The debugger automatically halts at each call
to this function as if a breakpoint were set on the call. You can use this feature to quickly reach the
code you are actually trying to debug without having to first find and set a breakpoint on it after
launching your application. You can also instruct Chrome Inspector not to suspend your program at the first
source-level statement being executed. When doing so, Sulong will instead execute your program until it
reaches a call to `__builtin_debugtrap()` before invoking the debugger. To enable this behaviour you need
pass the arguments `--inspect.Suspend=false` and `--inspect.WaitAttached=true` (or
`-Dpolyglot.inspect.Suspend=false` and `-Dpolyglot.inspect.WaitAttached=true` if you compiled Sulong
from source).

### Expression Evaluation

In general, Sulong supports evaluating expressions in the console as well as with watch expressions. 
However, the input language of these expressions is not the C or C++ language, since Sulong uses LLVM-IR 
code instead of C/C++ code. Therefore, there exists a special language based on C/C++ for Sulong's expression 
evaluation, which can be found in the next chapter. 

## Language Description for Expression Evaluation

As mentioned above, Sulong supports expression evaluation. This section describes the input language of these 
expressions. Concerning the execution order of subexpressions, the following holds:

* Building nested expressions (`ptr->elem + ((int)weight) - (root > 4 ? 0 : getRoot(4))`) is possible. 

* Using parenthesis (e.g. `a * (b + c)`) to group expressions is possible.  

* If feature A is listed above feature B in the following list and no parenthesis are present, then also feature 
A binds stronger than B. For example, multiplication is listed above the `<` compare operator. 
Therefore, `3 * a < 40` results in `(3 * a) < 40`.

### Expression description

The language, in which expressions for evaluations have to be written, provides the following features:

* Using constant values, i.e. integers (e.g. `13`), floating-point numbers (e.g. `3.4424` or `2e4`) and character constants (`'e'`)

* Using symbols (variables, objects, method names) that live in the source-level program (e.g. `age` or `personObj`)

* Accessing more complex symbols: 

  * Performing function calls (e.g. `foo(arg1, arg2)`) of functions that are defined in the source-level program. 
    * Developers can also define helper functions in their source-level program (e.g. allocating a String object on the heap) that can be executed via Sulong's expression evaluation. 
  * Accessing array elements (e.g. `arr[4]` or `elems[idx+1]`)
  * Accessing members of structured objects or pointers (e.g. `personObj.name`, `personPtr->name`)

* Determining the size of types (`sizeof(unsigned int*)`)

* Performing casts (e.g. `(int)(3.4+a)`)

* Using unary operators for
  * negating numbers (e.g. `-4` or `-amount`)
  * dereferencing of pointer values (`*ptr`)
  * performing bit flipping (`~4` or `~nElems`) of integer types
  * negating 'boolean' expressions (`!condition`). If `condition` is an integer type, `0` is considered as `false`, every other value is considered as `true`

* Using multiplication, division and the modulo operator (e.g. `rate * hours`, `dist / time`, `nTotal % nSize`). The result of a division or a modulo operation depends on whether operands are unsigned or signed if they are of an integer type. 

* Using addition and subtraction (e.g. `a + b` or `nOld + nAdd - nRemove`)

* Bit shifting (e.g. `a >> 2` or `b << n2`) of integer types. For the `>>` operator, the result depends on whether the left operand is signed or unsigned. 

* Comparing expressions with common order relations: `<` (less than), `<=` (less than or equal), `>` and `>=` (greater than (or equal)). 
  * If both operands are of signed integer types, then the comparison is a signed integer comparison.  
  * If both operands are of integer types and at least one of them is of an unsigned integer type, then the comparison is an unsigned integer comparison. 

* Comparing expressions with common equality relations, which are `==` for equality and `!=` for inequality

* Performing bit-wise AND, OR and XOR operations (e.g. `nFlags & ~(1 << 3)`, `nFlags | (1 << 4)` or `nFlags ^ 1`). AND binds stronger than OR, OR binds stronger than XOR. 

* Performing logical AND and OR operations (e.g. `ptr!=null && ptr->a >= 3` or `invalid || noElemFound`). AND binds stronger than OR. Concerning evaluation, a 'short circuit evaluation' is applied, i.e. if `ptr` of the example above is `null`, then the second condition `ptr->a >= 3` is not evaluated. 

* Using the conditional operator `condition ? thenExpr : elseExpr`. If `condition` is true or other than `0`, then `thenExpr` is evaluated. Otherwise, `elseExpr` is evaluated. For finding the maximum of two numbers a and b, the expression would look like `a>b ? a : b`. 

### Type description

For some of the features listed above, it is necessary to specify a type. Sulong's expression evaluation therefore offers two possibilities: 

* Pre-defined types: 
  * signed integer types: `char` (8 bits), `short` (16 bits), `int` (32 bits), `long` (64 bits). These types can also be specified with the `signed` identifier (`signed char` , `signed short`, etc.).
  * unsigned integer types: `unsigned char`, `unsigned short`, `unsigned int`, `unsigned long`
  * floating-point types: `float` (32-bit), `double` (64 bit) and `long double` (LLVM 80 bit)
  * These basic types are converted implicitly from top to bottom, e.g. `a+b` results in an unsigned integer, if `a` is `unsigned` and `b` is `signed`. 
  * Pointer types are denoted by the asterisc symbol (e.g. `int*`)
  * Array types are denoted by square brackets (e.g. `long[]`). For the `sizeof(...)` operator, array types can also be specified with the number of elements (e.g. `sizeof(int[5])`). 

* User-defined types: Accessing user-defined types is done via the `typeof` operator and is only possible if there exists a symbol of this type in the source-level program. If e.g. a program uses its own structure such as `struct { int x; int y; } Point2D;` and there exists a `Point2D* p;`, then `typeof(p)` returns the type `Point2D*` (a pointer type to `Point2D`). 

## FAQ

### I am compiling my bitcode files on another system. Can the source-level debugger find the sources on my system?

In general, debug information in LLVM bitcode files uses absolute paths to identify the
location of source code. Usually this requires you to imitate the compiling system's
directory structure in which your sources reside so that the debugger can find them.
To work around this limitation, in C/C++ code you can use the `#line` preprocessor
directive to manually define a path for the source file.

    #line <current line number> <filename/path you want to be used by the debugger for the current file>

You can also use a Sulong-specific format as filename to make the paths pseudo-relative.

    "truffle-relpath://<property>//<relative path/filename>"

Sulong will use the system property `property`, which you can set dynamically, to resolve
`relative path/filename` against.

### Can I also debug my program on LLVM-IR level?

Sulong also contains preliminary support for debugging program on the level of LLVM IR.
This feature is only in the early stages and may contain bugs. To use it, you need to
replace the option `-Dpolyglot.llvm.enableLVI=true` with `-Dpolyglot.llvm.llDebug=true`.
Please note that both `enableLVI` and `llDebug` cannot be used together. Also, to
debug on LLVM-IR level you need to use `llvm-dis` to disassemble the `*.bc` files
that you want to execute. Sulong expects an equally named `*.ll` file in the same
directory as the `*.bc` files it executes. To disassemble all `*.bc` files in a
directory you can use this command:

    for f in $(find . -type f -name *.bc) ; do llvm-dis -o ${f::-3}.ll $f ; done

If you run this command on Sulong's `mxbuild` directory you may notice several
warnings about files with incompatible debug information. These are bitcode files
that were compiled using DragonEgg, which emits a version of LLVM debug information
that is incompatible with modern LLVM releases. You can safely ignore those warnings.
Sulong does not require any debug information to be present in either `*.bc` or `*.ll`
files to debug on the level of LLVM-IR.

You can also specify a separate location for the `*.ll` file corresponding to a `*.bc`
file using the `llDebug.Sources` argument. When using this option you need to specify
the path of both the `*.ll` and the `*.bc` file which it describes. While the option
itself can only be specified once, you can pass it an arbitrary number of path mappings.

    -Dpolyglot.llvm.llDebug.Sources=<path to *.bc file>=<path to *.ll file>[:<path to *.bc file>=<path to *.ll file>]*

### I am calling Sulong from Java. Can I debug both my Java code and the program running on Sulong at the same time?

You cannot yet debug Java code using the Chrome inspector. However, you can launch the
Chrome inspector from within your Java code. Please refer to the
[documentation of the GraalVM Tools](http://www.graalvm.org/docs/reference-manual/tools/)
for details on how to do that. This enables you to debug your Java code using your Java
debugger of choice while debugging the code executed by Sulong in the Chrome inspector.

### How can I generate a trace of how Sulong executes my program?

Sulong can produce an LLVM IR-level trace of its program execution. You can enable
this feature by passing the `--llvm.traceIR<...>` option to `lli`. This option takes a
single argument denoting the target for the trace output.

* `stdout` or `out`: prints the trace to `stdout`

* `stderr` or `err`: prints the trace to `stderr`

* `file://<path>`: prints the trace to the file denoted by `path`

Please note that in order to use this feature you also need to enable IR-level
debugging as described above by setting `-Dpolyglot.llvm.llDebug=true` and
ensuring that sulong can find `.ll` files for the bitcode files it executes.
