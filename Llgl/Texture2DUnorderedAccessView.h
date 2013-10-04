#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture2DUnorderedAccessView) : public Texture2DView
{
public:
	friend class Texture2D;
	virtual ~Texture2DUnorderedAccessView() override;
	uint32_t getMipLevel() const;
protected:
	Texture2DUnorderedAccessView(Texture2DPtr parentTexture, uint32_t mipLevel);
	virtual void initializeDriver() = 0;
private:
	void initialize();
	uint32_t _mipLevel;
};

LLGL_NAMESPACE_END;