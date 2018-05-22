#include "cctx/cctx_compiler.h"
#include "cctx/cctx_platform.h"

#if defined CCTX_COMPILER_MSC
#	define CSP_STACK_WALKER
#elif defined CCTX_PLATFORM_ANDROID
#	define CSP_DLADDR
#endif

#ifdef CSP_STACK_WALKER
#	include "StackWalker/StackWalker.h"
#endif

class SymbolPrinter;

#ifdef CSP_STACK_WALKER
class CspStackWalker : public StackWalker
{
public:

	CspStackWalker(SymbolPrinter* a_printer = NULL);

protected:

	virtual void OnOutput(LPCSTR szText);

	SymbolPrinter* m_printer;
};

class CspCallStack
{
public:

	CspCallStack();
	void Set(HANDLE a_thread = NULL, CONTEXT* m_context = NULL);

	HANDLE m_thread;
	CONTEXT* m_context;
};

#endif

typedef void (*CspSymbolPrinterOutput)(const char* a_text, void* a_user_data);

class SymbolPrinter
{
public:

	SymbolPrinter();
	bool Initialize(CspSymbolPrinterOutput a_output, void* a_user_data = NULL);
	void PrintCallStack(const CspCallStack& stack = CspCallStack());

private:

	CspSymbolPrinterOutput m_output;
	void* m_output_user_data;

#ifdef CSP_STACK_WALKER
	CspStackWalker m_walker;
	friend class CspStackWalker;
#endif
};
