#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Context)
{
public:

private:
	std::vector<ObjectWeakPtr> _objects;
};


LLGL_NAMESPACE_END;