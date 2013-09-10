#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_ENUM(MapType)
{
	Read,
	Write
};

LLGL_ENUM(ResourceType)
{
	Buffer,
	Texture1D,
	Texture2D,
	Texture3D
};

LLGL_CLASS(Resource) : public ContextChild
{
public:
	virtual ~Resource() override;
	FormatPtr getFormat() const;
	uint32_t isStreaming() const;
	uint32_t isMapped() const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getDepth() const; 
	uint32_t getNumDimensions() const;
	ResourceType getType() const;

	void* map(MapType type);
	void unmap();

protected:
	Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, FormatPtr format, bool isStreaming);
	Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, FormatPtr format, bool isStreaming);
	Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, uint32_t depth, FormatPtr format, bool isStreaming);

	virtual void initialize() override;
	virtual void* mapImpl(MapType type) = 0;
	virtual void unmapImpl() = 0;

private:
	FormatPtr _format;
	bool _isStreaming;
	bool _isMapped;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	uint32_t _numDims;
	ResourceType _resourceType;
};


LLGL_NAMESPACE_END;