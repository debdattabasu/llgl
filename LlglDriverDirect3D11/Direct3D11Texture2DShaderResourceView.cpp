#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11Texture2DShaderResourceView::Direct3D11Texture2DShaderResourceView(Texture2DPtr parentTexture) :
	Texture2DShaderResourceView(parentTexture), _srv(0)
{

}

Direct3D11Texture2DShaderResourceView::~Direct3D11Texture2DShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

ID3D11ShaderResourceView* Direct3D11Texture2DShaderResourceView::getDirect3D11ShaderResourceView() const
{
	return _srv;
}


void Direct3D11Texture2DShaderResourceView::initializeDriver()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getDirect3D11Device();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getParentResource()->getFormat())->getDxgiFormatTyped();
	auto tex2d = std::dynamic_pointer_cast<Direct3D11Texture2D>(getParentResource())->getDirect3D11Texture2D();

	HRESULT hr = S_OK;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;

	uint32_t arraySize = getParentResource()->getArraySize();
	if(arraySize == 1)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = -1;
	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
		srvd.Texture2DArray.MostDetailedMip = 0;
		srvd.Texture2DArray.MipLevels = -1;
		srvd.Texture2DArray.FirstArraySlice = 0;
		srvd.Texture2DArray.ArraySize = arraySize;
	}

	hr = dev->CreateShaderResourceView(tex2d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

LLGL_NAMESPACE_END2;