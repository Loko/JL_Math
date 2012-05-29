#include "jlCore.h"
#include <cstdlib>
#include <cstdarg>
#include <cstdio>

static jlAssertionHandler curHandler = 0;
	
void jlSetAssertionHandler(jlAssertionHandler handler) {
	curHandler = handler;
}

jlAssertionHandler jlGetAssertionHandler() {
	return curHandler;
}

jlAssertionBehavoir jlReportAssertion(const char8 *cond, const char8 *file, int32 line, const char8 *msg, ...) {
	const int32 MAX_ASSERT_BUFFER_SIZE = 1024;
	char8 buffer[MAX_ASSERT_BUFFER_SIZE];
	va_list args;
	if (msg) {
		va_start(args, msg);
		vsprintf_s(buffer, MAX_ASSERT_BUFFER_SIZE, msg, args);
		va_end(args);
	}
	if (curHandler) {
		return jlGetAssertionHandler()(cond, buffer, file, line);
	} else {
		printf("Cond: %s File: %s Line: %d \nMessage: %s\n", cond, file, line, buffer);
		#if TBD_DEFAULT_ON_ASSERT == TBD_ON_ASSERT_HALT
			return BEHAVOIR_HALT;
		#else
			abort();
			return BEHAVOIR_EXIT; // unreachable, to prevent annoying compiler warning
		#endif
	}
}
