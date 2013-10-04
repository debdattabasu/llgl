#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DRenderTargetView) : public Texture2DView
{
public:
	friend class Texture2D;
	virtual ~Texture2DRenderTargetView() override;
	uint32_t getMipLevel() const;
	uint32_t getArrayIndex() const;


protected:
	Texture2DRenderTargetView(Texture2DPtr parentTexture, uint32_t mipLevel, uint32_t arrayIndex);
	virtual void initializeDriver() = 0;
private:
	void initialize();
	uint32_t _mipLevel;
	uint32_t _arrayIndex;
};

LLGL_NAMESPACE_END;