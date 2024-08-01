#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "texture.h"
#include "glsl.h"
#include "Camera.h"
#include "Object.h"
#include "SceneBuilder.h"

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------
#define DELTA_TIME 10
#define WIDTH 800
#define HEIGHT 600


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------


static Camera MainCamera;

vector<Object*> objects;


//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    MainCamera.Move(key);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{

    // Define background
    glClearColor(0, 0, 0.5, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for(int i = 0; i < objects.size(); i++)
    {
		objects[i]->Render();
    }

    glutSwapBuffers();
}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
    glutTimerFunc(DELTA_TIME, Render, 0);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glewInit();
}

//------------------------------------------------------------
// void InitCamera()
//------------------------------------------------------------

void InitCamera()
{
    MainCamera = Camera(glm::vec3(0, 3, -10.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0));

    MainCamera.SetProjection(WIDTH, HEIGHT);

    MainCamera.SetLightPos(glm::vec3(0, 3, -10));

    Object::camera = &MainCamera;
}


//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->InitBuffers();
    }
}

void InitObjects() {

    objects = CreateObjects();
}

int main(int argc, char** argv)
{
    InitCamera();
    InitGlutGlew(argc, argv);
    InitObjects();
    InitBuffers();
    glutKeyboardFunc(keyboardHandler);
    

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
