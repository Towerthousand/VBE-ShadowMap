#include "Prop.hpp"
#include "Camera.hpp"

Prop::Prop(std::string meshID, std::string texId) :
	pos(0.0f), rot(0.0f), scale(1.0f), tex(Textures.get(texId)), drawMode(Real) {
	model.mesh = Meshes.get(meshID);
	model.program = Programs.get("propShader");
}

void Prop::update(float deltaTime) {
	(void) deltaTime;
	transform = mat4f(1.0f);
	transform = glm::translate(transform,pos);
	transform = glm::rotate(transform,rot.x,vec3f(1,0,0));
	transform = glm::rotate(transform,rot.y,vec3f(0,1,0));
	transform = glm::rotate(transform,rot.z,vec3f(0,0,1));
	transform = glm::scale(transform,scale);
}

void Prop::draw() const {
	Camera* cam = (Camera*)getGame()->getObjectByName("cam");
	switch (drawMode) {
		case Real:
			model.program = Programs.get("propShader");
			model.program->uniform("modelViewProjectionMatrix")->set(cam->projection*cam->view*fullTransform);
			model.program->uniform("sampler")->set(tex);
			model.draw();
			break;
		case ShadowMap:
			break;
	}
}
