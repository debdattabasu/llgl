#pragma once
#include "Prerequisites.h"

LLGL_NAMESPACE(Llgl);

LLGL_CLASS(Texture3DShaderResourceView) : public Texture3DView
{
public:
	friend class Texture3D;
	virtual ~Texture3DShaderResourceView() override;

protected:
	Texture3DShaderResourceView(Texture3DPtr parentTexture);
	virtual void initializeDriver() = 0;
private:
	void initialize();

};

LLGL_NAMESPACE_END;