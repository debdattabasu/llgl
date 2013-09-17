#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Context) : public Context
{
public:
	Direct3D11Context();
	~Direct3D11Context() override;
	CapabilitiesPtr getCapabilities() override;
	BufferPtr createBufferImpl(uint32_t width, FormatPtr format, bool isStreaming) override;
	Texture1DPtr createTexture1DImpl(uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming) override;
	Texture2DPtr createTexture2DImpl(uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming) override;
	Texture3DPtr createTexture3DImpl(uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format, bool isStreaming) override;
	FormatPtr createFormatImpl(FormatType type, uint32_t vectorSize) override;
	void initialize();

	ID3D11Device* _dev;
	ID3D11DeviceContext* _ctx;
	D3D_FEATURE_LEVEL _featureLevel;
};

LLGL_NAMESPACE_END2;