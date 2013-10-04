#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DSlice) : public ContextChild
{
public:
	friend class Texture2D;
	virtual ~Texture2DSlice() override;
	FormatPtr getFormat() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getMipLevel() const;
	Texture2DPtr getParentTexture() const;
	void copyFrom(Texture2DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t destOffsetX, uint32_t destOffsetY);
protected:
	Texture2DSlice(Texture2DPtr parentTexture, uint32_t mipLevel);
	void initialize();
	virtual void initializeDriver() = 0;
	virtual void copyFromDriver(Texture2DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t destOffsetX, uint32_t destOffsetY) = 0;
private:
	uint32_t _mipLevel;
	Texture2DPtr _parentTexture;
};

LLGL_NAMESPACE_END;