#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture2D::Direct3D11Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height,
	uint32_t numMips, uint32_t arraySize, FormatPtr format):
	Texture2D(parentContext, width, height, numMips, arraySize, format), _tex2d(0)
{

}

Direct3D11Texture2D::~Direct3D11Texture2D()
{
	SAFE_RELEASE(_tex2d);
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
	td.ArraySize = getArraySize();
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
}

Texture2DShaderResourceViewPtr Direct3D11Texture2D::getShaderResourceViewDriver()
{
	return Texture2DShaderResourceViewPtr(new Direct3D11Texture2DShaderResourceView(shared_from_this()));
}

Texture2DUnorderedAccessViewPtr Direct3D11Texture2D::getUnorderedAccessViewDriver(uint32_t mipLevel)
{
	return Texture2DUnorderedAccessViewPtr(new Direct3D11Texture2DUnorderedAccessView(shared_from_this(), mipLevel));
}

Texture2DRenderTargetViewPtr Direct3D11Texture2D::getRenderTargetViewDriver(uint32_t mipLevel, uint32_t arrayIndex)
{
	return Texture2DRenderTargetViewPtr(new Direct3D11Texture2DRenderTargetView(shared_from_this(), mipLevel, arrayIndex));
}

Texture2DDepthStencilViewPtr Direct3D11Texture2D::getDepthStencilViewDriver(uint32_t mipLevel, uint32_t arrayIndex)
{
	return Texture2DDepthStencilViewPtr(new Direct3D11Texture2DDepthStencilView(shared_from_this(), mipLevel, arrayIndex));
}

Texture2DDataAccessViewPtr Direct3D11Texture2D::getDataAccessViewDriver(uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex)
{
	return Texture2DDataAccessViewPtr(new Direct3D11Texture2DDataAccessView(shared_from_this(), 
		offsetX, offsetY, width, height, mipLevel, arrayIndex));
}

LLGL_NAMESPACE_END2;