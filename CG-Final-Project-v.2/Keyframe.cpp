#include "Keyframe.h"
#include <glm/gtc/matrix_transform.hpp>

void Keyframe::Apply(glm::mat4* model, float delta_time)
{
	const glm::vec3 empty;
	const glm::vec4 empty4;

	//scale
	if (scale != empty) {
		*model *= glm::scale(*model, scale * delta_time);
	}

	//translate
	if (translate != empty) {
		*model = glm::translate(glm::mat4(1.0f), translate * delta_time) * *model;
	}

	//rotate
	if (rotation != empty4) {
		//if the pivot is empty use the standard function
		if (pivot == empty) {
			*model = glm::rotate(*model, glm::radians(rotation.w * delta_time), glm::vec3(rotation.x, rotation.y, rotation.z));
		}
		else {
			//translate the model to the pivot point, rotate it and translate it back
			*model = glm::translate(*model, pivot);
			*model = glm::rotate(*model, glm::radians(rotation.w * delta_time), glm::vec3(rotation.x, rotation.y, rotation.z));
			*model = glm::translate(*model, -(pivot));
		}
	}
}