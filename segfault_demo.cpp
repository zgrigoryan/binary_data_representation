// segfault_demo.cpp
//
// Build:   g++ -g -O0 segfault_demo.cpp -o segfault_demo
// Run:     ./segfault_demo       (this will SEGV)
// macOS:   lldb ./segfault_demo core.*
// Linux:   gdb  ./segfault_demo core
//
// Purpose: show how an invalid pointer looks in the dump.

#include <cstdlib>
#include <cstdint>
#include <iostream>

int main()
{
    std::uintptr_t bad = 0xDEADBEEF;          // clearly bogus address
    std::cout << "About to dereference 0x" << std::hex << bad << std::dec << '\n';

    // Force a segmentation fault
    int value = *reinterpret_cast<int*>(bad); 

    std::cout << "This never prints: " << value << '\n';
    return EXIT_SUCCESS;
}
