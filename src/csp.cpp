#include "csp.h"

#if defined CSP_DL
#	include <unwind.h>
#	include <dlfcn.h>
#	include <cxxabi.h>
#elif defined CSP_BACKTRACE
#   include <execinfo.h>
#   include <stdlib.h>
#endif

// Windows
//	https://github.com/JochenKalmbach/StackWalker
// Android
//	http://stackoverflow.com/questions/8115192/android-ndk-getting-the-backtrace
// Linux
//	https://oroboro.com/printing-stack-traces-file-line/
// MacOS BSD
// https://developer.apple.com/legacy/library/documentation/Darwin/Reference/ManPages/man3/backtrace.3.html
// iOS
//	http://iosdevelopertips.com/debugging/debugging-trick-to-dump-call-stack-of-current-thread.html
//	https://github.com/gustafsson/backtrace/blob/master/README.md

#ifdef CSP_STACK_WALKER

CspStackWalker::CspStackWalker()
	: m_printer(NULL)
{
}

CspStackWalker::CspStackWalker(SymbolPrinter* a_printer, int a_options)
	: StackWalker(a_options)
	, m_printer(a_printer)
{
}

void CspStackWalker::OnOutput(LPCSTR szText)
{
	if(m_printer)
	{
		(m_printer->m_output)(szText, m_printer->m_output_user_data);
	}
}

#endif // CSP_STACK_WALKER

#ifdef CSP_DL

//----------------------------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------------------------
_Unwind_Reason_Code CspDlUnwindCallStack(struct _Unwind_Context* a_context, void* a_arg)
{
	CspCallStack* stack = (CspCallStack*)a_arg;
	uintptr_t pc = _Unwind_GetIP(a_context);
	if (pc)
	{
		if (stack->m_dl_entries_count == CspCallStack::dl_entries_count_max)
		{
			return _URC_END_OF_STACK;
		}
		else
		{
			stack->m_dl_entries[stack->m_dl_entries_count++] = reinterpret_cast<void*>(pc);
		}
	}
	return _URC_NO_REASON;
}

#endif // CSP_DL

CspCallStack::CspCallStack()
#if defined CSP_STACK_WALKER
	: m_thread(NULL)
	, m_context(NULL)
#elif defined CSP_DL
	: m_dl_entries_count(0)
#elif defined CSP_BACKTRACE
    : m_entries_count(entries_count_max + 1)
#elif defined CSP_NS
    : m_ns_lines(NULL)
#endif
{
}

#ifndef CSP_NS

CspCallStack::~CspCallStack()
{
}

#endif // CSP_NS

#if defined CSP_STACK_WALKER

void CspCallStack::SetWin32(HANDLE a_thread, CONTEXT* a_context)
{
	m_thread = a_thread;
	m_context = a_context;
}

#elif defined CSP_DL

void CspCallStack::SetDl()
{
	m_dl_entries_count = 0;
	_Unwind_Backtrace(&CspDlUnwindCallStack, this);
}

#elif defined CSP_BACKTRACE

void CspCallStack::SetBacktrace()
{
    m_entries_count = backtrace(m_entries, entries_count_max);
}

#endif

SymbolPrinter::SymbolPrinter()
	: m_output(NULL)
	, m_output_user_data(NULL)
{
}

bool SymbolPrinter::Initialize(CspSymbolPrinterOutput a_output, void* a_user_data)
{
	m_output = a_output;
	m_output_user_data = a_user_data;

#ifdef CSP_STACK_WALKER
	// Invoke explicit constructor
	int walker_options = (StackWalker::RetrieveSymbol | StackWalker::RetrieveLine);
	m_walker.CspStackWalker::CspStackWalker(this, walker_options);
#endif

	return true;
}

#ifndef CSP_NS

void SymbolPrinter::PrintCallStack(const CspCallStack* a_stack)
{
#if defined CSP_STACK_WALKER

	HANDLE stack_thread = NULL;
	CONTEXT* stack_context = NULL;

	if(stack_thread == NULL)
	{
		stack_thread = GetCurrentThread();
		stack_context = NULL;
	}
	else
	{
		stack_thread = a_stack->m_thread;
		stack_context = a_stack->m_context;
	}
	m_walker.ShowCallstack(stack_thread, stack_context, NULL, m_output_user_data);

#elif defined CSP_DL

	for(size_t i = 0; i < a_stack.m_dl_entries_count; ++i)
	{
		const void* address = a_stack.m_dl_entries[i];
//		const char* module_name = "";
		const char* symbol_name = "";
		const char* demangled_name = NULL;

		Dl_info dl_info;
		if (dladdr(address, &dl_info) != 0)
		{
//			if (dl_info.dli_fname != NULL)
//			{
//				module_name = dl_info.dli_fname;
//			}

			if (dl_info.dli_sname != NULL)
			{
				symbol_name = dl_info.dli_sname;

				int demangle_status = 0;
				demangled_name = __cxxabiv1::__cxa_demangle(symbol_name, 0, 0, &demangle_status);
				if ((demangled_name != NULL) && (demangle_status == 0))
				{
					symbol_name = demangled_name;
				}
			}
		}

		(*m_output)(name, m_output_user_data);

		if (demangled_name != NULL)
		{
			free(demangled_name);
		}
	}

#elif defined CSP_BACKTRACE

	CspCallStack local_stack;
	CspCallStack* stack = NULL;
	if (a_stack == NULL)
	{
		stack = local_stack;
		local_stack.SetBacktrace();
	}
	else
	{
		stack = a_stack;
	}
	char** symbols = backtrace_symbols(stack->m_entries, stack->m_entries_count);
	if (symbols != NULL)
	{
		for (int i = 0; i < stack->m_entries_count; ++i)
		{
			const char* symbol = symbols[i];
			if (symbol != NULL)
			{
				(*m_output)(symbol, m_output_user_data);
			}
		}
		free(symbols);
	}

#endif
}

#endif // CSP_NS
