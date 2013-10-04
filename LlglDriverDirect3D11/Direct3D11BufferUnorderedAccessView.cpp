#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11BufferUnorderedAccessView::Direct3D11BufferUnorderedAccessView(BufferPtr parentBuffer) :
	BufferUnorderedAccessView(parentBuffer), _uav(0)
{

}

Direct3D11BufferUnorderedAccessView::~Direct3D11BufferUnorderedAccessView()
{
	SAFE_RELEASE(_uav);
}

void Direct3D11BufferUnorderedAccessView::initializeRaw()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto numElements = getParentBuffer()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentBuffer())->_buf;
	
	HRESULT hr;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	uavd.Format = dxgiFmtTyped;
	uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.FirstElement = 0;
	uavd.Buffer.NumElements =  numElements;
	uavd.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
	hr = dev->CreateUnorderedAccessView(buf, &uavd, &_uav);
	CHECK_HRESULT(hr);

}

void Direct3D11BufferUnorderedAccessView::initializeFormatted()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto dxgiFmtTyped = std::dynamic_pointer_cast<Direct3D11Format>(getFormat())->getDxgiFormatTyped();
	auto numElements = getParentBuffer()->getWidth();
	auto buf = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentBuffer())->_buf;
	
	HRESULT hr;
	D3D11_UNORDERED_ACCESS_VIEW_DESC uavd;
	ZeroMemory(&uavd, sizeof(uavd));
	uavd.Format = dxgiFmtTyped;
	uavd.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
	uavd.Buffer.FirstElement = 0;
	uavd.Buffer.NumElements =  numElements;
	uavd.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
	hr = dev->CreateUnorderedAccessView(buf, &uavd, &_uav);
	CHECK_HRESULT(hr);
}

void Direct3D11BufferUnorderedAccessView::initializeImpl()
{
	if (getFormat()->getUsage() == FormatUsage::RawBuffer) initializeRaw();
	else initializeFormatted();
}

LLGL_NAMESPACE_END2;