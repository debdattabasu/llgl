#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2D) : public Resource, public std::enable_shared_from_this<Texture2D> 
{
public:
	friend class Context;
	virtual ~Texture2D() override;
	Texture2DShaderResourceViewPtr getShaderResourceView();
	Texture2DUnorderedAccessViewPtr getUnorderedAccessView(uint32_t mipLevel);
	Texture2DRenderTargetViewPtr getRenderTargetView(uint32_t mipLevel, uint32_t arrayIndex);
	Texture2DDepthStencilViewPtr getDepthStencilView(uint32_t mipLevel, uint32_t arrayIndex);
	Texture2DDataAccessViewPtr getDataAccessView(uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex);

	uint32_t getWidth(uint32_t mipLevel = 0) const;
	uint32_t getHeight(uint32_t mipLevel = 0) const;
	uint32_t getNumMips() const;
	uint32_t getArraySize() const;
protected:
	Texture2D(ContextPtr parentContext, uint32_t width, uint32_t height, uint32_t numMips, FormatPtr format);
	virtual void initializeDriver() = 0;
	virtual Texture2DShaderResourceViewPtr getShaderResourceViewDriver() = 0;
	virtual Texture2DUnorderedAccessViewPtr getUnorderedAccessViewDriver(uint32_t mipLevel) = 0;
	virtual Texture2DRenderTargetViewPtr getRenderTargetViewDriver(uint32_t mipLevel, uint32_t arrayIndex) = 0;
	virtual Texture2DDepthStencilViewPtr getDepthStencilViewDriver(uint32_t mipLevel, uint32_t arrayIndex) = 0;
	virtual Texture2DDataAccessViewPtr getDataAccessViewDriver(uint32_t offsetX, uint32_t offsetY, 
		uint32_t width, uint32_t height, uint32_t mipLevel, uint32_t arrayIndex) = 0;
private:
	void initialize() override;
	uint32_t _width;
	uint32_t _height;
	uint32_t _numMips;
	uint32_t _arraySize;
};

LLGL_NAMESPACE_END;