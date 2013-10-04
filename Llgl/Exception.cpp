#include "Library.h"

LLGL_NAMESPACE(Llgl);
Exception::Exception(const std::string& what) : std::exception(what.c_str())
{
}

#define str(x) std::string(#x)
#ifndef LLGL_EXCEPTION_DEFINE
	#define LLGL_EXCEPTION_DEFINE(exceptionClassName)\
			exceptionClassName##Exception::exceptionClassName##Exception(const std::string& what) : \
				Exception((str(exceptionClassName) +"Exception:: " + what).c_str()) {} \
			exceptionClassName##Exception::exceptionClassName##Exception() : \
				Exception((str(exceptionClassName) +"Exception").c_str()) {} \
		
#endif

LLGL_EXCEPTION_DEFINE(InvalidArgument);
LLGL_EXCEPTION_DEFINE(InvalidOperation);
LLGL_EXCEPTION_DEFINE(OutOfMemory);
LLGL_EXCEPTION_DEFINE(UnexpectedError);
LLGL_EXCEPTION_DEFINE(NotDriveremented);
LLGL_EXCEPTION_DEFINE(UnsupportedFeature);


LLGL_NAMESPACE_END;