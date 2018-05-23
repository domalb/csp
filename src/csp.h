#include "cctx/cctx_compiler.h"
#include "cctx/cctx_platform.h"

#if defined CCTX_COMPILER_MSC
#	define CSP_STACK_WALKER
#elif (defined CCTX_COMPILER_GCC || defined CCTX_COMPILER_CLANG)
#	define CSP_DL
#endif

#if defined CSP_STACK_WALKER
#	include "StackWalker/StackWalker.h"
#elif defined CSP_DL
#endif

class SymbolPrinter;

#ifdef CSP_STACK_WALKER
class CspStackWalker : public StackWalker
{
public:

	CspStackWalker();
	CspStackWalker(SymbolPrinter* a_printer, int a_options);

private:

	// Empty virtuals to prevent output
	virtual void OnSymInit(LPCSTR szSearchPath, DWORD symOptions, LPCSTR szUserName) {}
	virtual void OnLoadModule(LPCSTR img, LPCSTR mod, DWORD64 baseAddr, DWORD size, DWORD result, LPCSTR symType, LPCSTR pdbName, ULONGLONG fileVersion) {}
	virtual void OnDbgHelpErr(LPCSTR szFuncName, DWORD gle, DWORD64 addr) {}

	virtual void OnOutput(LPCSTR szText);

	SymbolPrinter* m_printer;
};
#endif // CSP_STACK_WALKER

#ifdef CSP_DL
#endif

class CspCallStack
{
public:

	CspCallStack();
#if defined CSP_STACK_WALKER
	void SetWin32(HANDLE a_thread = NULL, CONTEXT* m_context = NULL);
#elif defined CSP_DL
	void SetDl();
#endif

#if defined CSP_STACK_WALKER
	HANDLE m_thread;
	CONTEXT* m_context;
#elif defined CSP_DL
	size_t m_dl_entries_count;
	enum { dl_entries_count_max = 100 };
	void* m_dl_entries[dl_entries_count_max];
#endif
};

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
