# C Symbol Printer

Get symbols text from call stack and globals.
Works on Windows, MacOSX, Linux, iOS and Android

## Using the code
```c++
#include "csp.h"

CspPrinter printer;
printer.PrintCallstack();
```
## Implementation
Windows implementation is based on [JochenKalmbach/StackWalker](https://github.com/JochenKalmbach/StackWalker)
