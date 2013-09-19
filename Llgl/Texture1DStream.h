#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DStream) : public ContextChild
{
public:
	friend class Context;
	LLGL_CLASS(MapDesc)
	{
	public:
		char* data;
	};
	virtual ~Texture1DStream() override;
	FormatPtr getFormat() const;
	bool isMapped() const;
	uint32_t getWidth() const;
	MapDesc map();
	void unmap();
	void readFrom(Texture1DSlicePtr src, uint32_t offset);
	void writeTo(Texture1DSlicePtr dest, uint32_t offset);
protected:
	Texture1DStream(ContextPtr parentContext, uint32_t width, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual MapDesc mapImpl() =0;
	virtual void unmapImpl() =0;
	virtual void readFromImpl(Texture1DSlicePtr src, uint32_t offset) = 0;
	virtual void writeToImpl(Texture1DSlicePtr dest, uint32_t offset) = 0;
private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;