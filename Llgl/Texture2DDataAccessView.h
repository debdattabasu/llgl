#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DDataAccessView) : public Texture2DView
{
public:
	friend class Texture2D;
	virtual ~Texture2DDataAccessView() override;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getOffsetX() const;
	uint32_t getOffsetY() const;
	uint32_t getMipLevel() const;
	uint32_t getArrayIndex() const;
	
	void copyFrom(Texture2DDataAccessViewPtr src);
	void getData(void* data);
	void setData(void* data);

protected:
	Texture2DDataAccessView(Texture2DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex);
	virtual void initializeDriver() = 0;
	virtual void copyFromDriver(Texture2DDataAccessViewPtr src) = 0;
	virtual void getDataDriver(void* data) = 0;
	virtual void setDataDriver(void* data) = 0;
private:
	void initialize();
	uint32_t _offsetX;
	uint32_t _offsetY;
	uint32_t _width;
	uint32_t _height;
	uint32_t _mipLevel; 
	uint32_t _arrayIndex;
};

LLGL_NAMESPACE_END;