#include "csp.h"

#include <iostream>

#if defined CCTX_COMPILER_MSC

void csp_test_output(const char* a_text, void* a_user_data)
{
	OutputDebugStringA(a_text);
}

// Printing the call stack of the current thread

void csp_test_cur_thread_func1(void* a_arg)
{
	SymbolPrinter printer;
	printer.Initialize(&csp_test_output);
	printer.PrintCallStack();
}

void csp_test_cur_thread_func2(int* a_arg)
{
	csp_test_cur_thread_func1(a_arg);
}

// Printing the call stack of the current thread

void csp_test_cur_exception_func1(void* a_arg)
{
	int* p = NULL;
	int val = 4 + *p;
	std::cout << "test " << val << " " << std::endl;
}

void csp_test_cur_exception_func2(int* a_arg)
{
	csp_test_cur_exception_func1(a_arg);
}

// The exception filter function:
LONG WINAPI csp_test_exception_filter(EXCEPTION_POINTERS* pExp, DWORD dwExpCode)
{
	CspCallStack stack;
	stack.SetWin32(GetCurrentThread(), pExp->ContextRecord);
	SymbolPrinter printer;
	printer.Initialize(&csp_test_output);
	printer.PrintCallStack(&stack);

	return EXCEPTION_EXECUTE_HANDLER;
}

// Main

int main()
{
//	csp_test_cur_thread_func2(&foo);

	__try
	{
		int foo = 0;
		csp_test_cur_exception_func2(&foo);
	}
	__except (csp_test_exception_filter(GetExceptionInformation(), GetExceptionCode()))
	{
	}

	return 0;
}

#elif defined CSP_BACKTRACE

void csp_backtrace_test_output(const char* a_text, void* a_user_data)
{
    std::cout << a_text << std::endl;
}

int main(int argc, const char * argv[])
{
    SymbolPrinter printer;
    printer.Initialize(&csp_backtrace_test_output);
    printer.PrintCallStack();
    
    return 0;
}

#elif defined CSP_NS

void csp_ns_test_output(const char* a_text, void* a_user_data)
{
    std::cout << a_text << std::endl;
}

int main(int argc, const char * argv[])
{
    SymbolPrinter printer;
    printer.Initialize(&csp_ns_test_output);
    printer.PrintCallStack();
    
    return 0;
}

#endif
