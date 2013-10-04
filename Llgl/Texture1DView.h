#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture1DView) : public TextureView
{
public:
	virtual ~Texture1DView() override;
	Texture1DPtr getParentResource() const;
protected:
	Texture1DView(Texture1DPtr parentTexture);
};

LLGL_NAMESPACE_END;