#ifndef PLAYERCAMERA_HPP
#define PLAYERCAMERA_HPP
#include "commons.hpp"

class Camera : public GameObject {
	public:
		Camera(const std::string &cameraName,const vec3f& pos = vec3f(0.0f), const vec3f& rot = vec3f(0.0f));

		void update(float deltaTime);

		vec3f pos;
		vec3f rot;
		mat4f projection;
		mat4f view;
};

#endif // PLAYERCAMERA_HPP
