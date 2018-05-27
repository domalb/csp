#include "csp.h"

#if defined CSP_NS

#import <Foundation/Foundation.h>

CspCallStack::~CspCallStack()
{
    if (m_ns_lines != NULL)
    {
        NSArray<NSString*>* lines = (__bridge_transfer NSArray<NSString*>*)m_ns_lines;
        lines = nil;
    }
}

void CspCallStack::SetNs()
{
    if (m_ns_lines != NULL)
    {
        NSArray<NSString*>* lines = (__bridge_transfer NSArray<NSString*>*)m_ns_lines;
        lines = nil;
    }
    NSArray<NSString*>* lines = [NSThread callStackSymbols];
    m_ns_lines = (__bridge_retained void*)lines;
}

void SymbolPrinter::PrintCallStack(const CspCallStack* a_stack)
{
    NSArray<NSString*>* lines = nil;
    if (a_stack == NULL)
    {
        lines = [NSThread callStackSymbols];
    }
    else
    {
        lines = (__bridge NSArray<NSString*>*)a_stack->m_ns_lines;
    }
    if (lines != nil)
    {
        NSUInteger lines_count = [lines count];
        for(NSUInteger i = 0; i < lines_count; ++i)
        {
            NSString* line = [lines objectAtIndex:i];
            if (line != nil)
            {
                const char* line_buff = [line UTF8String];
                if (line_buff != NULL)
                {
                    (*m_output)(line_buff, m_output_user_data);
                }
            }
        }
    }
}
#endif // CSP_NS
