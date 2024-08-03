#pragma once
#include "PrimitiveMesh.h"

class Skybox : public PrimitiveMesh
{

public:

	Skybox();

	void Render() override;
};

