#include "Texture_Class.h"
#include "texture.h"

void Texture::LoadCubeMap(vector<string> texture_paths)
{

	// Creates the cubemap texture object
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	for (int texture = 0; texture < texture_paths.size(); texture++)
	{
		unsigned int width, height;
		unsigned char* data = loadBMP(texture_paths[texture].c_str(), width, height, true);
		if (!data) {
			throw "No data found in texture";
		}

		glTexImage2D
		(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + texture,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			data
		);
		delete[] data;
	}
}

void Texture::Load(char* texture_path)
{
	this->id = loadBMP(texture_path);
	this->textureType = GL_TEXTURE_2D;
}
