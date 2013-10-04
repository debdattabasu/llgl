#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DUnorderedAccessView) : public Texture1DView
{
public:
	friend class Texture1D;
	virtual ~Texture1DUnorderedAccessView() override;
	uint32_t getMipLevel() const;
protected:
	Texture1DUnorderedAccessView(Texture1DPtr parentTexture, uint32_t mipLevel);
	virtual void initializeDriver() = 0;
private:
	void initialize();
	uint32_t _mipLevel;
};

LLGL_NAMESPACE_END;