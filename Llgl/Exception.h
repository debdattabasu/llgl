#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Exception) : public std::exception
{
public:
	Exception(const std::string& what);

};		

LLGL_EXCEPTION_DECLARE(InvalidArgument);
LLGL_EXCEPTION_DECLARE(InvalidOperation);
LLGL_EXCEPTION_DECLARE(OutOfMemory);
LLGL_EXCEPTION_DECLARE(UnexpectedError);
LLGL_EXCEPTION_DECLARE(NotImplemented);
LLGL_EXCEPTION_DECLARE(FileAccess);

LLGL_NAMESPACE_END;
