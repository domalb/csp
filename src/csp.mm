#include "csp.h"

#if defined CSP_NS

#import <Foundation/Foundation.h>

void CspCallStack::SetNs()
{
    NSArray<NSString*>* lines = [NSThread callStackSymbols];
    NSUInteger lines_count = [lines count];
    for(NSUInteger i = 0; i < lines_count; ++i)
    {
        NSString* line = [lines objectAtIndex:i];
        const char* 
    }
#endif // CSP_NS
