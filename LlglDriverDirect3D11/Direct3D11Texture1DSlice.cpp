#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture1DSlice::Direct3D11Texture1DSlice(Texture1DPtr parentTexture, uint32_t mipLevel):
	Texture1DSlice(parentTexture, mipLevel), _uav(0)
{

}

Direct3D11Texture1DSlice::~Direct3D11Texture1DSlice()
{
	SAFE_RELEASE(_uav);
}

void Direct3D11Texture1DSlice::initializeDriver()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto tex = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentTexture())->_tex1d;
	HRESULT hr = S_OK;
	if(caps->numUnorderedAccessSlots())
	{

		D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
		ZeroMemory(&uavd, sizeof(uavd));
		uavd.Format = dxgiFmtTyped;
		uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
		uavd.Texture1D.MipSlice = getMipLevel();
		hr = dev->CreateUnorderedAccessView(tex, &uavd, &_uav);
		CHECK_HRESULT(hr);
	}
}

void Direct3D11Texture1DSlice::copyFromDriver(Texture1DSlicePtr src, uint32_t srcOffset, uint32_t srcWidth, uint32_t destOffset) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(src->getParentTexture())->_tex1d; 
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentTexture())->_tex1d; 
	uint32_t srcSubRes = src->getMipLevel();
	uint32_t destSubRes = getMipLevel();
	D3D11_BOX bx;
	bx.left = srcOffset; 
	bx.right = srcOffset + srcWidth;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffset , 0, 0, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;