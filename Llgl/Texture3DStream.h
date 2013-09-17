#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DStream) : public ContextChild
{
public:
	friend class Context;
	virtual ~Texture3DStream() override;
	FormatPtr getFormat() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getDepth() const;
	bool isMapped() const;
	void* map();
	void unmap();
protected:
	Texture3DStream(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void* mapImpl() = 0;
	virtual void unmapImpl() = 0;
private:
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	FormatPtr _format;
};

LLGL_NAMESPACE_END;