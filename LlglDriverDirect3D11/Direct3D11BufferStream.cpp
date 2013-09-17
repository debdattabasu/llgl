#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);

Direct3D11BufferStream::Direct3D11BufferStream(ContextPtr parentContext, uint32_t width, FormatPtr format):
	BufferStream(parentContext, width, format), _buf(0)
{

}

Direct3D11BufferStream::~Direct3D11BufferStream()
{
	SAFE_RELEASE(_buf);
}


void Direct3D11BufferStream::initializeImpl()
{
	auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
	auto elementSize = getFormat()->getSize();
	auto numElements = getWidth();

	HRESULT hr = S_OK;
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = numElements * elementSize;
	bd.Usage = D3D11_USAGE_STAGING;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	hr = dev->CreateBuffer(&bd, NULL, &_buf);
	CHECK_HRESULT(hr);

}

void* Direct3D11BufferStream::mapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	HRESULT hr = S_OK;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(_buf, 0, D3D11_MAP_READ_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	return rs.pData;
}

void Direct3D11BufferStream::unmapImpl() 
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ctx->Unmap(_buf, 0);
}

LLGL_NAMESPACE_END2;