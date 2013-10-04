#include "Library.h"

LLGL_NAMESPACE(Llgl);

Texture2DDataAccessView::Texture2DDataAccessView(Texture2DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex) :
	Texture2DView(parentTexture), _offsetX(offsetX), _offsetY(offsetY), _width(width), _height(height), 
	_mipLevel(mipLevel), _arrayIndex(arrayIndex)
{

}

Texture2DDataAccessView::~Texture2DDataAccessView()
{

}

uint32_t Texture2DDataAccessView::getOffsetX() const
{
	return _offsetX;
}

uint32_t Texture2DDataAccessView::getOffsetY() const
{
	return _offsetY;
}

uint32_t Texture2DDataAccessView::getWidth() const
{
	return _width;
}

uint32_t Texture2DDataAccessView::getHeight() const
{
	return _height;
}

uint32_t Texture2DDataAccessView::getMipLevel() const
{
	return _mipLevel;
}

uint32_t Texture2DDataAccessView::getArrayIndex() const
{
	return _arrayIndex;
}

void Texture2DDataAccessView::getData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");

	Context::LockGuard lock(getParentContext()); 
	getDataDriver(data);
}

void Texture2DDataAccessView::setData(void* data)
{
	if(data == 0) throw InvalidArgumentException("argument null");
	
	Context::LockGuard lock(getParentContext()); 
	setDataDriver(data);
}

void Texture2DDataAccessView::initialize()
{
	if(getMipLevel() + 1 > getParentResource()->getNumMips() 
		|| getArrayIndex() + 1 > getParentResource()->getArraySize())
		throw InvalidArgumentException("out of bounds");

	if(getWidth() == 0 || getHeight() == 0) throw InvalidArgumentException("invalid dimensions");
	if((getOffsetX() + getWidth()) > getParentResource()->getWidth(getMipLevel())
		|| (getOffsetY() + getHeight()) > getParentResource()->getHeight(getMipLevel())) 
		throw InvalidArgumentException("out of bounds");

	Context::LockGuard lock(getParentContext()); 
	initializeDriver();
}

void Texture2DDataAccessView::copyFrom(Texture2DDataAccessViewPtr src)
{
	if (!src->getParentResource()->getFormat()->equals(getParentResource()->getFormat()))
		throw InvalidArgumentException("format mismatch");
	if (src->getWidth() != getWidth() || src->getHeight() != getHeight())
		throw InvalidArgumentException("dimension mismatch");	

  	Context::LockGuard lock(getParentContext());
	copyFromDriver(src);
}

LLGL_NAMESPACE_END;