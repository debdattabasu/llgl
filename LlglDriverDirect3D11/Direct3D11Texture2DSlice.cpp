#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture2DSlice::Direct3D11Texture2DSlice(Texture2DPtr parentTexture, uint32_t mipLevel):
	Texture2DSlice(parentTexture, mipLevel), _uav(0), _rtv(0), _dsv(0)
{

}

Direct3D11Texture2DSlice::~Direct3D11Texture2DSlice()
{
	SAFE_RELEASE(_uav);
	SAFE_RELEASE(_dsv);
	SAFE_RELEASE(_rtv);
}

void Direct3D11Texture2DSlice::initializeImpl()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto dxgiFmtDepthTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatDepthTyped();
	auto tex = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentTexture())->_tex2d;
	HRESULT hr = S_OK;
	bool isDepth = getFormat()->getUsage() == FormatUsage::DepthTexture;

	if(isDepth)
	{
		D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
		ZeroMemory(&dsvd, sizeof(dsvd));
		dsvd.Format = dxgiFmtDepthTyped;
		dsvd.ViewDimension= D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = getMipLevel();
		hr = dev->CreateDepthStencilView(tex, &dsvd, &_dsv);
		CHECK_HRESULT(hr);
	}
	else
	{
		D3D11_RENDER_TARGET_VIEW_DESC rtvd ;
		ZeroMemory(&rtvd, sizeof(rtvd));
		rtvd.Format = dxgiFmtTyped;
		rtvd.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvd.Texture2D.MipSlice = getMipLevel();
		hr = dev->CreateRenderTargetView(tex, &rtvd, &_rtv);
		CHECK_HRESULT(hr);

		if(caps->numUnorderedAccessSlots())
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
			uavd.Format = dxgiFmtTyped;
			uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
			uavd.Texture2D.MipSlice = getMipLevel();
			hr = dev->CreateUnorderedAccessView(tex, &uavd, &_uav);
			CHECK_HRESULT(hr);
		}
	}
}

void Direct3D11Texture2DSlice::copyFromImpl(Texture2DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t destOffsetX, uint32_t destOffsetY) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(src->getParentTexture())->_tex2d; 
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentTexture())->_tex2d; 
	uint32_t srcSubRes = src->getMipLevel();
	uint32_t destSubRes = getMipLevel();
	D3D11_BOX bx;
	bx.left = srcOffsetX; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, 0, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;