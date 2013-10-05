#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture1DUnorderedAccessView::Direct3D11Texture1DUnorderedAccessView(Texture1DPtr parentTexture, uint32_t mipLevel) :
	Texture1DUnorderedAccessView(parentTexture, mipLevel), _uav(0)
{

}

Direct3D11Texture1DUnorderedAccessView::~Direct3D11Texture1DUnorderedAccessView()
{
	SAFE_RELEASE(_uav);
}

void Direct3D11Texture1DUnorderedAccessView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentResource())->_tex1d;
	
	HRESULT hr = S_OK;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	uavd.Format = dxgiFmtTyped;

	uint32_t arraySize = getParentResource()->getArraySize();
	if(arraySize == 1)
	{
		uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1D;
		uavd.Texture1D.MipSlice = getMipLevel();
	}
	else
	{
		uavd.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE1DARRAY;
		uavd.Texture1DArray.MipSlice = getMipLevel();
		uavd.Texture1DArray.FirstArraySlice = 0;
		uavd.Texture1DArray.ArraySize = arraySize;
	}
	
	hr = dev->CreateUnorderedAccessView(tex, &uavd, &_uav);
	CHECK_HRESULT(hr);
	
}

LLGL_NAMESPACE_END2;