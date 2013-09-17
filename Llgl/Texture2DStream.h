#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DStream) : public ContextChild
{
public:
	friend class Context;
	virtual ~Texture2DStream() override;
	FormatPtr getFormat() const;
	bool isMapped() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	void* map();
	void unmap();
protected:
	Texture2DStream(ContextPtr parentContext, uint32_t width, uint32_t height, FormatPtr format);
	void initialize();
	virtual void initializeImpl() = 0;
	virtual void* mapImpl() = 0;
	virtual void unmapImpl() = 0;
private:
	FormatPtr _format;
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
};

LLGL_NAMESPACE_END;