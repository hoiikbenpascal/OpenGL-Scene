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
#include "InputHandler.h"

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
static InputHandler Handler;

vector<Object*> objects;

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
    glutTimerFunc(DELTA_TIME, Render, 0);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glewInit();
}


//------------------------------------------------------------
// void InitControls
// Initializes the controls
//------------------------------------------------------------
void keyboardHandler(unsigned char key, int a, int b)
{
    Handler.HandleKeyboard(key);
}

void MouseHandler(int x, int y) {
    Handler.HandleMouse(x, y);
}

void HandleClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_UP) {
            Handler.Reset();
        }
    }
}

void InitControls() {
    Handler = InputHandler(&MainCamera);

    glutMouseFunc(HandleClick);
    glutMotionFunc(MouseHandler);
    //glutPassiveMotionFunc(HandleMouse);

    glutKeyboardFunc(keyboardHandler);
}

//------------------------------------------------------------
// void InitCamera
// Initializes the camera
//------------------------------------------------------------
void InitCamera()
{
    MainCamera = Camera(glm::vec3(0, 3, -10.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0));

    MainCamera.SetProjection(WIDTH, HEIGHT);

    MainCamera.SetLightPos(glm::vec3(0, 50, -1000));

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
    glm::vec3 light_pos = MainCamera.GetLightPos();
}

int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitCamera();
    InitControls();
    InitObjects();
    InitBuffers();
    

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
