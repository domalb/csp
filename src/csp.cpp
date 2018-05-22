#include "csp.h"

#ifdef CSP_STACK_WALKER

CspStackWalker::CspStackWalker(SymbolPrinter* a_printer)
	: m_printer(a_printer)
{
}

void CspStackWalker::OnOutput(LPCSTR szText)
{
	if(m_printer)
	{
		(m_printer->m_output)(szText, m_printer->m_output_user_data);
	}
}

CspCallStack::CspCallStack()
	: m_thread(NULL)
	, m_context(NULL)
{
}

void CspCallStack::Set(HANDLE a_thread, CONTEXT* a_context)
{
	m_thread = a_thread;
	m_context = a_context;
}

#endif

SymbolPrinter::SymbolPrinter()
	: m_output(NULL)
	, m_output_user_data(NULL)
	, m_walker(this)
{
}

bool SymbolPrinter::Initialize(CspSymbolPrinterOutput a_output, void* a_user_data)
{
	m_output = a_output;
	m_output_user_data = a_user_data;

// #ifdef CSP_STACK_WALKER
// 	if (m_walker.LoadModules() == FALSE)
// 	{
// 		return false;
// 	}
// #endif

	return true;
}

void SymbolPrinter::PrintCallStack(const CspCallStack& stack)
{
#ifdef CSP_STACK_WALKER
	HANDLE stack_thread = stack.m_thread;
	CONTEXT* stack_context = (CONTEXT*)stack.m_context;
	if(stack_thread == NULL)
	{
		stack_thread = GetCurrentThread();
		stack_context = NULL;
	}
	m_walker.ShowCallstack(stack_thread, stack_context);
#endif
}
