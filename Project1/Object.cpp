#include "Object.h"
#include <glm/detail/type_mat4x4.hpp>

Camera* Object::camera;

/// <summary>
///	x,y,z detail the ammount of x,y,z rotation range: 0-1
///	angle is the rotation per frame
/// </summary>
void Object::SetRotation(float x, float y, float z, float angle)
{
	if(x,y,z,angle == 0)
	{
		rotating = false;
		return;
	}
	this->rotation = glm::vec4(x, y, z, angle);
	rotating = true;
}