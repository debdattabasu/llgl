#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3D) : public Texture3D
{
public:
	Direct3D11Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	~Direct3D11Texture3D() override;
	void initializeDriver() override;

	Texture3DDataAccessViewPtr getDataAccessViewDriver(uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, 
		uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevel) override;
	Texture3DShaderResourceViewPtr getShaderResourceViewDriver() override;
	Texture3DUnorderedAccessViewPtr getUnorderedAccessViewDriver(uint32_t mipLevel) override;

	ID3D11Texture3D* getDirect3D11Texture3D() const;
private:
	ID3D11Texture3D* _tex3d;
};

LLGL_NAMESPACE_END2;