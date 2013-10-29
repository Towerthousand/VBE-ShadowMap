#include "Camera.hpp"

Camera::Camera(const vec3f& pos, const vec3f& rot)
	: pos(pos), rot(rot), projection(1.0f), view(1.0f) {
	this->setName("cam");
	this->setUpdatePriority(2);
}

void Camera::update(float deltaTime) {
	(void) deltaTime;
	if(Input::isKeyDown(sf::Keyboard::LShift)) pos.z -= 10*deltaTime;
	if(Input::isKeyDown(sf::Keyboard::Space)) pos.z += 10*deltaTime;
	view = mat4f(1.0f);
	view = glm::rotate(view,rot.x,vec3f(1,0,0));
	view = glm::rotate(view,rot.y,vec3f(0,1,0));
	view = glm::rotate(view,rot.z,vec3f(0,0,1));
	view = glm::translate(view, -pos);
}
