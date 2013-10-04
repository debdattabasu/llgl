#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11BufferShaderResourceView::Direct3D11BufferShaderResourceView(BufferPtr parentBuffer) :
	BufferShaderResourceView(parentBuffer), _srv(0)
{

}

Direct3D11BufferShaderResourceView::~Direct3D11BufferShaderResourceView()
{
	SAFE_RELEASE(_srv);
}

void Direct3D11BufferShaderResourceView::initializeRaw()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto numElements = getParentBuffer()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentBuffer())->_buf;

	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
	srvd.BufferEx.FirstElement = 0;
	srvd.BufferEx.NumElements = numElements;
	srvd.BufferEx.Flags = D3D11_BUFFEREX_SRV_FLAG_RAW;

	hr = dev->CreateShaderResourceView(buf, &srvd, &_srv);
	CHECK_HRESULT(hr);

}

void Direct3D11BufferShaderResourceView::initializeFormatted()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto elementSize = getFormat()->getSize();
	auto numElements = getParentBuffer()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentBuffer())->_buf;
	
	HRESULT hr;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
	ZeroMemory(&srvd, sizeof(srvd));
	srvd.Format = dxgiFmtTyped;
	srvd.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
	srvd.Buffer.FirstElement = 0;
	srvd.Buffer.ElementWidth = elementSize;
	srvd.Buffer.ElementOffset = 0;
	srvd.Buffer.NumElements = numElements;
	hr = dev->CreateShaderResourceView(buf, &srvd, &_srv);
	CHECK_HRESULT(hr);
}

void Direct3D11BufferShaderResourceView::initializeImpl()
{
	if (getFormat()->getUsage() == FormatUsage::RawBuffer) initializeRaw();
	else initializeFormatted();
}

LLGL_NAMESPACE_END2;