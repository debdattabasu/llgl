#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2D) : public ContextChild, public std::enable_shared_from_this<Texture2D> 
{
public:
	friend class Context;
	virtual ~Texture2D() override;
	FormatPtr getFormat() const;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getHeight(uint32_t mipLevel = 0) const;
	uint32_t getNumMips()  const;
	Texture2DSlicePtr getSlice(uint32_t mipLevel);
protected:
	Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual Texture2DSlicePtr getSliceImpl(uint32_t mipLevel) = 0;
private:
	uint32_t _width;
	uint32_t _height;
	uint32_t _numMips;
	FormatPtr _format;
};

LLGL_NAMESPACE_END;