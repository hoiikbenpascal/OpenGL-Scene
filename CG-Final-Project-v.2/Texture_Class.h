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

	Texture(GLenum type) {
		id = GLuint();
		textureType = type;
		
	}

	void Activate();

	void LoadCubeMap(vector<string> texture_paths);

	void Load(char* texture_path);
};



