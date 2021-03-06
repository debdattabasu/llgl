#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1D) : public Resource, public std::enable_shared_from_this<Texture1D>
{
public:
	friend class Context;
	virtual ~Texture1D() override;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getNumMips() const;
	uint32_t getArraySize() const;

	Texture1DDataAccessViewPtr getDataAccessView(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex);
	Texture1DShaderResourceViewPtr getShaderResourceView();
	Texture1DUnorderedAccessViewPtr getUnorderedAccessView(uint32_t mipLevel);

protected:
	Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	virtual void initializeDriver() = 0;
	virtual Texture1DDataAccessViewPtr getDataAccessViewDriver(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex) = 0;
	virtual Texture1DShaderResourceViewPtr getShaderResourceViewDriver() = 0;
	virtual Texture1DUnorderedAccessViewPtr getUnorderedAccessViewDriver(uint32_t mipLevel) = 0;
private:
	void initialize() override;
	uint32_t _width;
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;