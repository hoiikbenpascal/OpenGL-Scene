#pragma once
#include "PrimitiveMesh.h"

class Skybox : public PrimitiveMesh
{

public:

	Skybox(std::vector<string> paths);

	void Render() override;
};

