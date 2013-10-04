#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(BufferDataAccessView) : public BufferView
{
public:
	friend class Buffer;
	virtual ~BufferDataAccessView() override;
	uint32_t getWidth() const;
	uint32_t getOffset() const;
	void copyFrom(BufferDataAccessViewPtr src);
	void getData(void* data);
	void setData(void* data);
protected:
	BufferDataAccessView(BufferPtr parentBuffer, uint32_t offset, uint32_t width);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void copyFromImpl(BufferDataAccessViewPtr src) = 0;
	virtual void getDataImpl(void* data) = 0;
	virtual void setDataImpl(void* data) = 0;
private:
	uint32_t _offset;
	uint32_t _width;
};

LLGL_NAMESPACE_END;