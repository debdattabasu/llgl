#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture1DShaderResourceView::Direct3D11Texture1DShaderResourceView(Texture1DPtr parentTexture) :
	Texture1DShaderResourceView(parentTexture), _srv(0)
{

}

Direct3D11Texture1DShaderResourceView::~Direct3D11Texture1DShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

ID3D11ShaderResourceView* Direct3D11Texture1DShaderResourceView::getDirect3D11ShaderResourceView() const
{
	return _srv;
}

void Direct3D11Texture1DShaderResourceView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex1d = std::dynamic_pointer_cast<Direct3D11Texture1D>(getParentResource())->getDirect3D11Texture1D();

	HRESULT hr = S_OK;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;

	uint32_t arraySize = getParentResource()->getArraySize();
	if(arraySize == 1)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		srvd.Texture1D.MostDetailedMip = 0;
		srvd.Texture1D.MipLevels = -1;
	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
		srvd.Texture1DArray.MostDetailedMip = 0;
		srvd.Texture1DArray.MipLevels = -1;
		srvd.Texture1DArray.FirstArraySlice = 0;
		srvd.Texture1DArray.ArraySize = arraySize;
	}
	
	hr = dev->CreateShaderResourceView(tex1d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;