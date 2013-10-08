#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

class Exception : public std::exception
{
public:
	Exception(const std::string& what) :
		std::exception(what.c_str()) {}

};

#define STR(x)	std::string(#x)	

#define LLGL_EXCEPTION(exceptionClassName) \
	class exceptionClassName##Exception : public Exception\
	{\
	public:\
		exceptionClassName##Exception(const std::string& what) : \
			Exception((STR(exceptionClassName) +"Exception:: " + what).c_str()) {}\
		exceptionClassName##Exception() : \
			Exception((STR(exceptionClassName) +"Exception").c_str()) {} \
	};


LLGL_EXCEPTION(InvalidArgument);
LLGL_EXCEPTION(InvalidOperation);
LLGL_EXCEPTION(OutOfMemory);
LLGL_EXCEPTION(UnexpectedError);
LLGL_EXCEPTION(NotImplemented);
LLGL_EXCEPTION(UnsupportedFeature);

#undef STR
#undef LLGL_EXCEPTION

LLGL_NAMESPACE_END;
