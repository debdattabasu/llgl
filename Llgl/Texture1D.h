#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1D) : public ContextChild, public std::enable_shared_from_this<Texture1D>
{
public:
	friend class Context;
	virtual ~Texture1D() override;
	FormatPtr getFormat() const;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getNumMips()  const;
	Texture1DSlicePtr getSlice(uint32_t mipLevel);
protected:
	Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual Texture1DSlicePtr getSliceImpl(uint32_t mipLevel) = 0;
private:
	FormatPtr _format;
	uint32_t _width;
	uint32_t _numMips;
};

LLGL_NAMESPACE_END;