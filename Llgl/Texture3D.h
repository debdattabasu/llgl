#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3D) : public Resource, public std::enable_shared_from_this<Texture3D>
{
public:
	friend class Context;
	virtual ~Texture3D() override;
	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getHeight(uint32_t mipLevel = 0) const;
	uint32_t getDepth(uint32_t mipLevel = 0) const;
	uint32_t getNumMips() const;

	Texture3DDataAccessViewPtr getDataAccessView(uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, 
		uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevel);
	Texture3DShaderResourceViewPtr getShaderResourceView();
	Texture3DUnorderedAccessViewPtr getUnorderedAccessView(uint32_t mipLevel);
protected:
	Texture3D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t depth, uint32_t numMips, FormatPtr format);
	void initialize();
	virtual void initializeDriver() = 0;
	virtual Texture3DDataAccessViewPtr getDataAccessViewDriver(uint32_t offsetX, uint32_t offsetY, uint32_t offsetZ, 
		uint32_t width, uint32_t height, uint32_t depth, uint32_t mipLevel) = 0;
	virtual Texture3DShaderResourceViewPtr getShaderResourceViewDriver() = 0;
	virtual Texture3DUnorderedAccessViewPtr getUnorderedAccessViewDriver(uint32_t mipLevel) = 0;
private:
	uint32_t _width;
	uint32_t _height;
	uint32_t _depth;
	uint32_t _numMips;
};

LLGL_NAMESPACE_END;