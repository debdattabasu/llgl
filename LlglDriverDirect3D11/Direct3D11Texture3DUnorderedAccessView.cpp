#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture3DUnorderedAccessView::Direct3D11Texture3DUnorderedAccessView(Texture3DPtr parentTexture, uint32_t mipLevel) :
	Texture3DUnorderedAccessView(parentTexture, mipLevel), _uav(0)
{

}

Direct3D11Texture3DUnorderedAccessView::~Direct3D11Texture3DUnorderedAccessView()
{
	SAFE_RELEASE(_uav);
}

ID3D11UnorderedAccessView* Direct3D11Texture3DUnorderedAccessView::getDirect3D11UnorderedAccessView() const
{
	return _uav;
}

void Direct3D11Texture3DUnorderedAccessView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex3d = std::dynamic_pointer_cast<Direct3D11Texture3D>(getParentResource())->getDirect3D11Texture3D();

	HRESULT hr = S_OK;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	uavd.Format = dxgiFmtTyped;
	uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE3D;
	uavd.Texture3D.MipSlice = getMipLevel();
	uavd.Texture3D.FirstWSlice = 0;
	uavd.Texture3D.WSize = getParentResource()->getDepth();
	hr = dev->CreateUnorderedAccessView(tex3d, &uavd, &_uav);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;