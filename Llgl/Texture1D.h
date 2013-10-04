#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1D) : public Texture, public std::enable_shared_from_this<Texture1D>
{
public:
	friend class Context;
	virtual ~Texture1D() override;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	Texture1DSlicePtr getSlice(uint32_t mipLevel);
	Texture1DDataAccessViewPtr getDataAccessView(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex);

protected:
	Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, FormatPtr format);
	void initialize();
	virtual void initializeDriver() = 0;
	virtual Texture1DSlicePtr getSliceDriver(uint32_t mipLevel) = 0;
	virtual Texture1DDataAccessViewPtr getDataAccessViewDriver(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex) = 0;
private:
	uint32_t _width;
};

LLGL_NAMESPACE_END;