#ifndef TEXTURE_HPP
#define TEXTURE_HPP


unsigned char* loadJPG(const char* imagepath, unsigned int& width, unsigned int& height);

// Load a .BMP file using custom loader that also returns the width, height and data of the image instead of initializing it in a texture
unsigned char* loadBMP(const char* imagepath, unsigned int& width, unsigned int& height, bool flip_y = false);

// Load a .BMP file using our custom loader
GLuint loadBMP(const char * imagepath);

//// Since GLFW 3, glfwLoadTexture2D() has been removed. You have to use another texture loading library, 
//// or do it yourself (just like loadBMP_custom and loadDDS)
//// Load a .TGA file using GLFW's own loader
//GLuint loadTGA_glfw(const char * imagepath);

// Load a .DDS file using GLFW's own loader
GLuint loadDDS(const char * imagepath);

#endif