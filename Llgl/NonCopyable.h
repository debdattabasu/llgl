#pragma once 
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(NonCopyable)
{
public:
	virtual ~NonCopyable() {} 
protected:
    NonCopyable() {}
private: 
    NonCopyable(const NonCopyable &);
    NonCopyable & operator = (const NonCopyable &);
};

LLGL_NAMESPACE_END;