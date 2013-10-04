#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferView::BufferView(BufferPtr parentBuffer) : ContextChild(parentBuffer->getParentContext()), 
	_parentBuffer(parentBuffer)
{

}

BufferView::~BufferView()
{

}

FormatPtr BufferView::getFormat() const
{
	return _parentBuffer->getFormat();
}

BufferPtr BufferView::getParentBuffer() const
{
	return _parentBuffer;
}

LLGL_NAMESPACE_END;