#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Context) : public Context
{
public:
	Direct3D11Context();
	~Direct3D11Context() override;
	CapabilitiesPtr getCapabilities() override;
	BufferPtr createBufferDriver(uint32_t width, FormatPtr format) override;
	Texture1DPtr createTexture1DDriver(uint32_t width, uint32_t numMips, FormatPtr format) override;
	Texture2DPtr createTexture2DDriver(uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format) override;
	Texture3DPtr createTexture3DDriver(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format) override;
	Texture3DStreamPtr createTexture3DStreamDriver(uint32_t width, uint32_t height, uint32_t depth, FormatPtr format) override;
	FormatPtr createFormatDriver(FormatType type, uint32_t vectorSize) override;
	void initialize();

	ID3D11Device* _dev;
	ID3D11DeviceContext* _ctx;
	D3D_FEATURE_LEVEL _featureLevel;
};

LLGL_NAMESPACE_END2;