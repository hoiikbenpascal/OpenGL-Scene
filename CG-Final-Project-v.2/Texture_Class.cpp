#include "Texture_Class.h"
#include "texture.h"

int Texture::textureAmmount = 0;

void Texture::Activate()
{
	glActiveTexture(GL_TEXTURE0 + tex_num);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void Texture::LoadCubeMap(vector<string> texture_paths)
{

	tex_num = textureAmmount;
	textureAmmount++;

	// Creates the cubemap texture object
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

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

		// These are very important to prevent seams
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	}
}



void Texture::Load(char* texture_path)
{
	this->id = loadBMP(texture_path);
	this->textureType = GL_TEXTURE_2D;
}
