#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DUnorderedAccessView) : public Texture3DView
{
public:
	friend class Texture3D;
	virtual ~Texture3DUnorderedAccessView() override;
	uint32_t getMipLevel() const;
protected:
	Texture3DUnorderedAccessView(Texture3DPtr parentTexture, uint32_t mipLevel);
	virtual void initializeDriver() = 0;
private:
	void initialize();
	uint32_t _mipLevel;
};

LLGL_NAMESPACE_END;