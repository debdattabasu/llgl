#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture3DSlice::Direct3D11Texture3DSlice(Texture3DPtr parentTexture, uint32_t mipLevel):
	Texture3DSlice(parentTexture, mipLevel), _uav(0)
{

}

Direct3D11Texture3DSlice::~Direct3D11Texture3DSlice()
{
	SAFE_RELEASE(_uav);
}

void Direct3D11Texture3DSlice::initializeDriver()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto tex = std::dynamic_pointer_cast<Direct3D11Texture3D>(getParentTexture())->_tex3d;
	HRESULT hr = S_OK;

	if(caps->numUnorderedAccessSlots())
	{
		D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
		uavd.Format = dxgiFmtTyped;
		uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
		uavd.Texture3D.MipSlice = getMipLevel();
		uavd.Texture3D.FirstWSlice = 0;
		uavd.Texture3D.WSize = getDepth();
		hr = dev->CreateUnorderedAccessView(tex, &uavd, &_uav);
		CHECK_HRESULT(hr);
	}
}

void Direct3D11Texture3DSlice::copyFromDriver(Texture3DSlicePtr src, uint32_t srcOffsetX, uint32_t srcOffsetY, uint32_t srcOffsetZ,
		uint32_t srcWidth, uint32_t srcHeight, uint32_t srcDepth, uint32_t destOffsetX, uint32_t destOffsetY, uint32_t destOffsetZ) 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Texture3D>(src->getParentTexture())->_tex3d; 
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Texture3D>(getParentTexture())->_tex3d; 
	uint32_t srcSubRes = src->getMipLevel();
	uint32_t destSubRes = getMipLevel();
	D3D11_BOX bx;
	bx.left = srcOffsetX ; 
	bx.right = srcOffsetX + srcWidth;
	bx.top = srcOffsetY;
	bx.bottom = srcOffsetY + srcHeight;
	bx.front = srcOffsetZ;
	bx.back = srcOffsetZ + srcDepth;
	ctx->CopySubresourceRegion(destRes, destSubRes, destOffsetX , destOffsetY, destOffsetZ, srcRes, srcSubRes, &bx);
}

LLGL_NAMESPACE_END2;