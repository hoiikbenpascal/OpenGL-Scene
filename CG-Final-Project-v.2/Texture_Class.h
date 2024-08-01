#pragma once
#include "glsl.h"
class Texture
{
	

public:
	GLuint id;
	GLenum textureType;

	Texture(GLenum type) {
		id = GLuint();
		textureType = type;
		glGenTextures(1, &id);

		if (textureType == GL_TEXTURE_CUBE_MAP) {
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// These are very important to prevent seams
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		}
	}

	//void Load(vector<std::string> textures);

	void Bind() {
		glBindTexture(textureType, id);
	}
};

