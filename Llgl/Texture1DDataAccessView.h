#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DDataAccessView) : public Texture1DView
{
public:
	friend class Texture1D;
	virtual ~Texture1DDataAccessView() override;
	uint32_t getWidth() const;
	uint32_t getOffset() const;
	uint32_t getMipLevel() const;
	uint32_t getArrayIndex() const;
	
	void copyFrom(Texture1DDataAccessViewPtr src);
	void getData(void* data);
	void setData(void* data);

protected:
	Texture1DDataAccessView(Texture1DPtr parentTexture, uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex);
	virtual void initializeDriver() = 0;
	virtual void copyFromDriver(Texture1DDataAccessViewPtr src) = 0;
	virtual void getDataDriver(void* data) = 0;
	virtual void setDataDriver(void* data) = 0;
private:
	void initialize();
	uint32_t _offset;
	uint32_t _width;
	uint32_t _mipLevel; 
	uint32_t _arrayIndex;
};

LLGL_NAMESPACE_END;