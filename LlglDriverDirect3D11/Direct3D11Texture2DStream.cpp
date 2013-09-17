#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11Texture2DStream::Direct3D11Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format):
	Texture2DStream(parentContext, width, height, format), _tex2d(0)
{

}

Direct3D11Texture2DStream::~Direct3D11Texture2DStream()
{
	SAFE_RELEASE(_tex2d);
}

void Direct3D11Texture2DStream::initializeImpl()
{
	auto caps = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->getCapabilities();
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTypeless = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTypeless();

	HRESULT hr = S_OK;
	D3D11_TEXTURE2D_DESC td; 
	ZeroMemory(&td, sizeof(td));
	td.Width = getWidth();
	td.Height = getHeight();
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = dxgiFmtTypeless;
	td.SampleDesc.Count = 1;
	td.Usage = D3D11_USAGE_STAGING;
	td.CPUAccessFlags = D3D11_CPU_ACCESS_READ|D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateTexture2D(&td, NULL, &_tex2d);
	CHECK_HRESULT(hr);
}

void* Direct3D11Texture2DStream::mapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(_tex2d, 0, D3D11_MAP_READ_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	return rs.pData;
}

void Direct3D11Texture2DStream::unmapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ctx->Unmap(_tex2d, 0);
}

LLGL_NAMESPACE_END2;