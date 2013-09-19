#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DSlice) : public ContextChild
{
public:
	friend class Texture1D;
	virtual ~Texture1DSlice() override;
	Texture1DPtr getParentTexture() const;
	FormatPtr getFormat() const;
	uint32_t getWidth() const;
	uint32_t getMipLevel() const;
	void copyFrom(Texture1DSlicePtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset);
protected:
	Texture1DSlice(Texture1DPtr parentTexture, uint32_t mipLevel);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(Texture1DSlicePtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) = 0;	
private:
	Texture1DPtr _parentTexture;
	uint32_t _mipLevel;
};

LLGL_NAMESPACE_END;