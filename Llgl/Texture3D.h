#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3D) : public Resource, public std::enable_shared_from_this<Texture3D>
{
public:
	friend class Context;
	virtual ~Texture3D() override;
	Texture3DSlicePtr getSlice(uint32_t mipLevel);
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getHeight(uint32_t mipLevel = 0) const;
	uint32_t getDepth(uint32_t mipLevel = 0) const;
	uint32_t getNumMips() const;
protected:
	Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	void initialize();
	virtual void initializeDriver() = 0;
	virtual Texture3DSlicePtr getSliceDriver(uint32_t mipLevel) = 0;
private:
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	uint32_t _numMips;
};

LLGL_NAMESPACE_END;