#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferVertexArrayView::BufferVertexArrayView(BufferPtr parentBuffer) :
	BufferView(parentBuffer)
{

}

BufferVertexArrayView::~BufferVertexArrayView()
{

}

void BufferVertexArrayView::initialize()
{
	Context::LockGuard lock(getParentContext()); 
	if(getFormat()->getUsage() != FormatUsage::General)
		throw InvalidArgumentException("vertex array views unsupported by format");
	initializeImpl();
}

LLGL_NAMESPACE_END;