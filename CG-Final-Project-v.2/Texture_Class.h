#pragma once
#include "glsl.h"
#include <vector>
class Texture
{
	

public:
	GLuint id;
	GLenum textureType;

	Texture(GLenum type) {
		id = GLuint();
		textureType = type;
		
	}

	void LoadCubeMap(vector<string> texture_paths);

	void Load(char* texture_path);

	void Bind() {
		glBindTexture(textureType, id);
	}
};

