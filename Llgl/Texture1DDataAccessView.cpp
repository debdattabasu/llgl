#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture1DDataAccessView::Texture1DDataAccessView(Texture1DPtr parentTexture, uint32_t offset, uint32_t width, 
	uint32_t mipLevel, uint32_t arrayIndex) :
	Texture1DView(parentTexture), _offset(offset), _width(width), _mipLevel(mipLevel), _arrayIndex(arrayIndex)
{

}

Texture1DDataAccessView::~Texture1DDataAccessView()
{

}

uint32_t Texture1DDataAccessView::getWidth() const
{
	return _width;
}

uint32_t Texture1DDataAccessView::getOffset() const
{
	return _offset;
}

uint32_t Texture1DDataAccessView::getMipLevel() const
{
	return _mipLevel;
}

uint32_t Texture1DDataAccessView::getArrayIndex() const
{
	return _arrayIndex;
}

void Texture1DDataAccessView::getData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");

	Context::LockGuard lock(getParentContext()); 
	getDataDriver(data);
}

void Texture1DDataAccessView::setData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");
	
	Context::LockGuard lock(getParentContext()); 
	setDataDriver(data);
}

void Texture1DDataAccessView::initialize()
{
	if(getMipLevel() + 1 > getParentResource()->getNumMips() 
		|| getArrayIndex() + 1 > getParentResource()->getArraySize())
		throw InvalidArgumentException("out of bounds");

	if(getWidth() == 0) throw InvalidArgumentException("invalid dimensions");
	if((getOffset() + getWidth()) > getParentResource()->getWidth(getMipLevel())) 
		throw InvalidArgumentException("out of bounds");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

void Texture1DDataAccessView::copyFrom(Texture1DDataAccessViewPtr src)
{
	if (!src->getParentResource()->getFormat()->equals(getParentResource()->getFormat()))
		throw InvalidArgumentException("format mismatch");
	if (!src->getWidth() == getWidth())
		throw InvalidArgumentException("dimension mismatch");	

  	Context::LockGuard lock(getParentContext());
	copyFromDriver(src);
}

LLGL_NAMESPACE_END;