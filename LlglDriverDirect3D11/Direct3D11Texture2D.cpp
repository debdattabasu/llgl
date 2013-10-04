#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture2D::Direct3D11Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height,
	uint32_t numMips, FormatPtr format):
	Texture2D(parentContext, width, height, numMips, format), _tex2d(0), _srv(0)
{

}

Direct3D11Texture2D::~Direct3D11Texture2D()
{
	SAFE_RELEASE(_tex2d);
	SAFE_RELEASE(_srv);
}

void Direct3D11Texture2D::initializeDriver()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto dxgiFmtDepthTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatDepthTyped();
	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.MipLevels = getNumMips();
	td.ArraySize = 1;
	td.Format = dxgiFmtTypeless;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_DEFAULT;
	bool isDepth = getFormat()->getUsage() == FormatUsage::DepthTexture;
	td.BindFlags = (isDepth)? D3D11_BIND_DEPTH_STENCIL: D3D11_BIND_RENDER_TARGET;	
	td.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	if(!isDepth && caps->numUnorderedAccessSlots())
		td.BindFlags |= D3D11_BIND_UNORDERED_ACCESS;
	hr = dev->CreateTexture2D(&td, NULL, &_tex2d);
	CHECK_HRESULT(hr);
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd ;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvd.Texture2D.MostDetailedMip = 0;
	srvd.Texture2D.MipLevels = -1;

	hr = dev->CreateShaderResourceView(_tex2d, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

Texture2DSlicePtr Direct3D11Texture2D::getSliceDriver(uint32_t mipLevel)
{
	return Texture2DSlicePtr(new Direct3D11Texture2DSlice(shared_from_this(), mipLevel));
}

LLGL_NAMESPACE_END2;