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

	CspStackWalker();
	CspStackWalker(SymbolPrinter* a_printer, int a_options);

private:

	virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName) {} // Empty to prevent output
	virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion) {} // Empty to prevent output
	virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr) {} // Empty to prevent output
	virtual void OnOutput(LPCSTR szText);

	SymbolPrinter* m_printer;
};

class CspCallStack
{
public:

	CspCallStack();
#if defined CCTX_COMPILER_MSC
	void SetWin32(HANDLE a_thread = NULL, CONTEXT* m_context = NULL);
#endif

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
