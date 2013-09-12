#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

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
	friend class Context;
	virtual ~Resource() override;
	FormatPtr getFormat() const;
	bool isStreaming() const;
	bool isMapped(uint32_t mipLevel, uint32_t arrayIndex) const;
	uint32_t getWidth() const;
	uint32_t getHeight() const;
	uint32_t getDepth() const; 
	uint32_t getNumDimensions() const;
	uint32_t getNumMips()  const;
	uint32_t getArraySize() const;
	ResourceType getType() const;
protected:
	Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	Resource(ContextPtr parentContext, ResourceType resType, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, uint32_t arraySize, FormatPtr format, bool isStreaming);
	virtual void initialize();
private:
	FormatPtr _format;
	bool _isStreaming;
	void setMapped(uint32_t mipLevel, uint32_t arrayIndex, bool value);
	std::vector<bool> _isMapped;
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	uint32_t _numDims;
	uint32_t _numMips;
	uint32_t _arraySize;
	ResourceType _resourceType;
};

LLGL_NAMESPACE_END;