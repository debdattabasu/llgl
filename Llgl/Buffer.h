#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Buffer) : public Resource, public std::enable_shared_from_this<Buffer>
{
public:
	friend class Context;
	virtual ~Buffer() override;
	uint32_t getWidth() const;
	BufferDataAccessViewPtr getDataAccessView(uint32_t offset, uint32_t width);
	BufferShaderResourceViewPtr getShaderResourceView();
	BufferUnorderedAccessViewPtr getUnorderedAccessView();
	BufferVertexArrayViewPtr getVertexArrayView();
	BufferIndexArrayViewPtr getIndexArrayView();
protected:
	Buffer(ContextPtr parentContext, uint32_t width, FormatPtr format);
	virtual void initializeDriver() = 0;
	virtual BufferDataAccessViewPtr getDataAccessViewDriver(uint32_t offset, uint32_t width) = 0;
	virtual BufferShaderResourceViewPtr getShaderResourceViewDriver() = 0;
	virtual BufferUnorderedAccessViewPtr getUnorderedAccessViewDriver() = 0;
	virtual BufferVertexArrayViewPtr getVertexArrayViewDriver() = 0;
	virtual BufferIndexArrayViewPtr getIndexArrayViewDriver() = 0;
private:
	void initialize() override;
	uint32_t _width;

};

LLGL_NAMESPACE_END;