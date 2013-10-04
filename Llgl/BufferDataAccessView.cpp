#include "Library.h"

LLGL_NAMESPACE(Llgl);

BufferDataAccessView::BufferDataAccessView(BufferPtr parentBuffer, uint32_t offset, uint32_t width) :
	BufferView(parentBuffer), _offset(offset), _width(width)
{

}

BufferDataAccessView::~BufferDataAccessView()
{

}

uint32_t BufferDataAccessView::getWidth() const
{
	return _width;
}

uint32_t BufferDataAccessView::getOffset() const
{
	return _offset;
}

void BufferDataAccessView::getData(void* data)
{
	Context::LockGuard lock(getParentContext()); 
	if(data == 0) throw InvalidArgumentException("argument null");
	getDataImpl(data);
}

void BufferDataAccessView::setData(void* data)
{
	Context::LockGuard lock(getParentContext()); 
	if(data == 0) throw InvalidArgumentException("argument null");
	setDataImpl(data);
}

void BufferDataAccessView::initialize()
{
	Context::LockGuard lock(getParentContext()); 
	if(getWidth() == 0) throw InvalidArgumentException("invalid dimensions");
	if((getOffset() + getWidth()) > getParentBuffer()->getWidth()) 
		throw InvalidArgumentException("out of bounds");
	initializeImpl();
}

void BufferDataAccessView::copyFrom(BufferDataAccessViewPtr src)
{
	Context::LockGuard lock(getParentContext());
	if (!src->getFormat()->equals(getFormat()))
		throw InvalidArgumentException("format mismatch");
	if (!src->getWidth() == getWidth())
		throw InvalidArgumentException("width mismatch");	
  	
	copyFromImpl(src);
}

LLGL_NAMESPACE_END;