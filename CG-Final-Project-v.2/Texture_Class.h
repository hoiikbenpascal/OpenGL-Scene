#pragma once
#include "glsl.h"
#include <vector>
class Texture
{
	static int textureAmmount;
	int tex_num;
public:
	GLuint id;
	GLenum textureType;
	bool repeat = false;

	Texture(GLenum type) {
		id = GLuint();
		textureType = type;
	}

	Texture() {}

	~Texture()
	{
		textureAmmount--;
	}

	void Activate();

	void LoadCubeMap(vector<string> texture_paths);

	void Load(const char* texture_path);
};



