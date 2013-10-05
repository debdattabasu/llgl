#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture3DDataAccessView) : public Texture3DDataAccessView
{
public:
	Direct3D11Texture3DDataAccessView(Texture3DPtr parentTexture, uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ,
		uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevel);
	~Direct3D11Texture3DDataAccessView() override;
	void initializeDriver() override;
	void copyFromDriver(Texture3DDataAccessViewPtr src) override;
	void getDataDriver(void* data) override;
	void setDataDriver(void* data) override;

	ID3D11Texture3D* getDirect3D11StagingTexture3D();
private:
	ID3D11Texture3D* _tex3d;
};

LLGL_NAMESPACE_END2;