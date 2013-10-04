#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferIndexArrayView::BufferIndexArrayView(BufferPtr parentBuffer) :
	BufferView(parentBuffer)
{

}

BufferIndexArrayView::~BufferIndexArrayView()
{

}

void BufferIndexArrayView::initialize()
{
	Context::LockGuard lock(getParentContext()); 
	if(getFormat()->getUsage() != FormatUsage::IndexBuffer)
		throw InvalidArgumentException("index array views unsupported by format");
	initializeImpl();
}

LLGL_NAMESPACE_END;