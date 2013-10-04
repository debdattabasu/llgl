#include "Library.h"

LLGL_NAMESPACE2(Llgl, Direct3D11);


Direct3D11BufferDataAccessView::Direct3D11BufferDataAccessView(BufferPtr parentBuffer, uint32_t offset, uint32_t width) :
	BufferDataAccessView(parentBuffer, offset, width), _buf(0)
{

}

Direct3D11BufferDataAccessView::~Direct3D11BufferDataAccessView()
{
	SAFE_RELEASE(_buf);
}

ID3D11Buffer* Direct3D11BufferDataAccessView::getDirect3D11StagingBuffer()
{
	if(!_buf)
	{
		auto dev = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_dev;
		auto elementSize = getParentResource()->getFormat()->getSize();
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
	return _buf;

}

void Direct3D11BufferDataAccessView::initializeDriver()
{

}

void Direct3D11BufferDataAccessView::copyFromDriver(BufferDataAccessViewPtr src)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Buffer>(src->getParentResource())->_buf;
	uint32_t srcOffset = src->getOffset();
	uint32_t srcWidth = src->getWidth();
	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->_buf;
	uint32_t destOffset = getOffset();
	auto elementSize = getParentResource()->getFormat()->getSize();

	D3D11_BOX bx;
	bx.left = srcOffset * elementSize; 
	bx.right = (srcOffset + srcWidth) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, 0, destOffset*elementSize , 0, 0, srcRes, 0, &bx);

}

void Direct3D11BufferDataAccessView::getDataDriver(void* data)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->_buf; 
	ID3D11Resource* destRes = getDirect3D11StagingBuffer();
	uint32_t elementSize = getParentResource()->getFormat()->getSize();

	D3D11_BOX bx;
	bx.left = getOffset() * elementSize; 
	bx.right = (getOffset() + getWidth()) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, 0, 0, 0, 0, srcRes, 0, &bx);

	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(destRes, 0, D3D11_MAP_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	memcpy(data, rs.pData, getWidth()*elementSize);

	ctx->Unmap(destRes, 0);
}

void Direct3D11BufferDataAccessView::setDataDriver(void* data)
{
	auto ctx = std::dynamic_pointer_cast<Direct3D11Context>(getParentContext())->_ctx;
	ID3D11Resource* srcRes = getDirect3D11StagingBuffer();
	uint32_t elementSize = getParentResource()->getFormat()->getSize();

	HRESULT hr;
	D3D11_MAPPED_SUBRESOURCE rs;
	rs.RowPitch = 0;
	rs.pData = 0;
	hr = ctx->Map(srcRes, 0, D3D11_MAP_WRITE, 0, &rs);
	CHECK_HRESULT(hr);
	memcpy(rs.pData, data, getWidth()*elementSize);
	ctx->Unmap(srcRes, 0);


	ID3D11Resource* destRes = std::dynamic_pointer_cast<Direct3D11Buffer>(getParentResource())->_buf;
	D3D11_BOX bx;
	
	bx.left = 0; 
	bx.right = (getWidth()) * elementSize;
	bx.top = 0;
	bx.bottom = 1;
	bx.front = 0;
	bx.back = 1;
	ctx->CopySubresourceRegion(destRes, 0, getOffset() * elementSize, 0, 0, srcRes, 0, &bx);

}

LLGL_NAMESPACE_END2;