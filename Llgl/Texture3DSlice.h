#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DSlice) : public ContextChild
{
public:
	friend class Texture3D;
	virtual ~Texture3DSlice() override;
	FormatPtr getFormat() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getDepth() const;
	uint32_t getMipLevel() const;
	Texture3DPtr getParentTexture() const;

	void copyFrom(Texture3DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ);
protected:
	Texture3DSlice(Texture3DPtr parentTexture, uint32_t mipLevel);
	void initialize();
	virtual void initializeDriver() = 0;
	virtual void copyFromDriver(Texture3DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) = 0;
private:
	Texture3DPtr _parentTexture;
	uint32_t _mipLevel;
};

LLGL_NAMESPACE_END;