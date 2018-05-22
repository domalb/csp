#include "csp.h"

// Printing the call stack of the current thread

void csp_test_output(const char* a_text, void* a_user_data)
{
	OutputDebugStringA(a_text);
}

void func1(void* a_arg)
{
	SymbolPrinter printer;
	printer.Initialize(&csp_test_output);
	printer.PrintCallStack();
}

void func2(int* a_arg)
{
	func1(a_arg);
}

int main()
{
	int foo = 0;
	func2(&foo);
    return 0;
}

