#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1D) : public Texture1D
{
public:
	Direct3D11Texture1D(ContextPtr parentContext, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format);
	~Direct3D11Texture1D() override;
	void initializeDriver() override;
	Texture1DDataAccessViewPtr getDataAccessViewDriver(uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex) override;
	Texture1DShaderResourceViewPtr getShaderResourceViewDriver() override;
	Texture1DUnorderedAccessViewPtr getUnorderedAccessViewDriver(uint32_t mipLevel) override;

	ID3D11Texture1D* getDirect3D11Texture1D() const;
private:
	ID3D11Texture1D* _tex1d;
};

LLGL_NAMESPACE_END2;