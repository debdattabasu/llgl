#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_ENUM(FormatType)
{
	Raw,
	Float, 
	Half,
	Int32, 
	Int16, 
	Uint32, 
	Uint16, 
	Snorm16,
	Snorm8, 
	Unorm16,
	Unorm8,
	Index16,
	Index32,
	DepthUnorm24Stencil8, 
	DepthFloat32Stencil24,
	DepthFloat32,
	DepthUnorm16 
};

LLGL_ENUM(FormatUsage)
{
	General, 
	RawBuffer, 
	IndexBuffer,
	DepthTexture
};

LLGL_CLASS(Format) : public ContextChild
{
public:
	friend class Context;
	virtual ~Format() override;
	FormatType getType();
	FormatUsage getUsage();
	uint32_t getSize();
	uint32_t getVectorSize();
	bool equals(FormatPtr other);
protected:
	Format(ContextPtr parentContext, FormatType type, uint32_t vectorSize);
	void initialize();
	virtual void initializeImpl() = 0;
private:
	FormatType _type;
	uint32_t _vectorSize;
};

LLGL_NAMESPACE_END;