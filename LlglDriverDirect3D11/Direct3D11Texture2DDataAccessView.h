#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture2DDataAccessView) : public Texture2DDataAccessView
{
public:
	Direct3D11Texture2DDataAccessView(Texture2DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex);
	~Direct3D11Texture2DDataAccessView() override;
	void initializeDriver() override;
	void copyFromDriver(Texture2DDataAccessViewPtr src) override;
	void getDataDriver(void* data) override;
	void setDataDriver(void* data) override;

	ID3D11Texture2D* getDirect3D11StagingTexture2D();
private:
	ID3D11Texture2D* _tex2d;
};

LLGL_NAMESPACE_END2;