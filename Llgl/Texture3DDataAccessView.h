#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DDataAccessView) : public Texture3DView
{
public:
	friend class Texture3D;
	virtual ~Texture3DDataAccessView() override;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getDepth() const;
	uint32_t getOffsetX() const;
	uint32_t getOffsetY() const;
	uint32_t getOffsetZ() const;
	uint32_t getMipLevel() const;
	
	void copyFrom(Texture3DDataAccessViewPtr src);
	void getData(void* data);
	void setData(void* data);

protected:
	Texture3DDataAccessView(Texture3DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ,
		uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevel);
	virtual void initializeDriver() = 0;
	virtual void copyFromDriver(Texture3DDataAccessViewPtr src) = 0;
	virtual void getDataDriver(void* data) = 0;
	virtual void setDataDriver(void* data) = 0;
private:
	void initialize();
	uint32_t _offsetX;
	uint32_t _offsetY;
	uint32_t _offsetZ;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	uint32_t _mipLevel; 
};

LLGL_NAMESPACE_END;