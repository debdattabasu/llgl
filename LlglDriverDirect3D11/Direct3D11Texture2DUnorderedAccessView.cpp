#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture2DUnorderedAccessView::Direct3D11Texture2DUnorderedAccessView(Texture2DPtr parentTexture, uint32_t mipLevel) :
	Texture2DUnorderedAccessView(parentTexture, mipLevel), _uav(0)
{

}

Direct3D11Texture2DUnorderedAccessView::~Direct3D11Texture2DUnorderedAccessView()
{
	SAFE_RELEASE(_uav);
}

void Direct3D11Texture2DUnorderedAccessView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex2d = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->_tex2d;

	HRESULT hr = S_OK;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	uavd.Format = dxgiFmtTyped;
	uint32_t arraySize = getParentResource()->getArraySize();
	if(arraySize == 1)
	{
		uavd.ViewDimension= D3D11_UAV_DIMENSION_TEXTURE2D;
		uavd.Texture2D.MipSlice = getMipLevel();
	}
	else
	{
		uavd.ViewDimension= D3D11_UAV_DIMENSION_TEXTURE2DARRAY;
		uavd.Texture2DArray.MipSlice = getMipLevel();
		uavd.Texture2DArray.FirstArraySlice = 0;
		uavd.Texture2DArray.ArraySize = arraySize;
	}
	hr = dev->CreateUnorderedAccessView(tex2d, &uavd, &_uav);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;