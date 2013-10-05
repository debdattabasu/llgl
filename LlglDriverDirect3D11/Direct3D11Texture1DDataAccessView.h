#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

LLGL_CLASS(Direct3D11Texture1DDataAccessView) : public Texture1DDataAccessView
{
public:
	Direct3D11Texture1DDataAccessView(Texture1DPtr parentTexture, uint32_t offset, uint32_t width, uint32_t mipLevel, uint32_t arrayIndex);
	~Direct3D11Texture1DDataAccessView() override;
	void initializeDriver() override;
	void copyFromDriver(Texture1DDataAccessViewPtr src) override;
	void getDataDriver(void* data) override;
	void setDataDriver(void* data) override;

	ID3D11Texture1D* getDirect3D11StagingTexture1D();
private:
	ID3D11Texture1D* _tex1d;
};

LLGL_NAMESPACE_END2;