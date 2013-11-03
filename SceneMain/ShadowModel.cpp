#include "ShadowModel.hpp"
#include "Camera.hpp"
#include "ShadowMapContainer.hpp"

ShadowModel::ShadowModel(std::string meshID, std::string texId) :
	pos(0.0f), rot(0.0f), scale(1.0f), tex(Textures.get(texId)), drawMode(Real) {
	model.mesh = Meshes.get(meshID);
	model.program = Programs.get("propShader");
}

void ShadowModel::update(float deltaTime) {
	(void) deltaTime;
	transform = mat4f(1.0f);
	transform = glm::translate(transform,pos);
	transform = glm::rotate(transform,rot.x,vec3f(1,0,0));
	transform = glm::rotate(transform,rot.y,vec3f(0,1,0));
	transform = glm::rotate(transform,rot.z,vec3f(0,0,1));
	transform = glm::scale(transform,scale);
}

void ShadowModel::draw() const {
	Camera* pCam = (Camera*)getGame()->getObjectByName("playerCam");
	Camera* sCam = (Camera*)getGame()->getObjectByName("sunCam");
	ShadowMapContainer* smc = (ShadowMapContainer*)getGame()->getObjectByName("smc");
	switch (drawMode) {
		case Real: {
			model.program = Programs.get("propShader");
			model.program->uniform("modelViewProjectionMatrix")->set(pCam->projection*pCam->view*fullTransform);
			model.program->uniform("modelMatrix")->set(fullTransform);
			model.program->uniform("viewMatrix")->set(pCam->view);
			glm::mat4 biasMatrix( //gets coords from [-1..1] to [0..1]
						0.5, 0.0, 0.0, 0.0,
						0.0, 0.5, 0.0, 0.0,
						0.0, 0.0, 0.5, 0.0,
						0.5, 0.5, 0.5, 1.0
						);
			model.program->uniform("depthMVP")->set(biasMatrix*(sCam->projection*sCam->view*fullTransform));
			model.program->uniform("sampler")->set(tex);
			model.program->uniform("depthBuffer")->set(smc->getDepthTexture());
			model.program->uniform("lightDir")->set(vec3f(sCam->view[0][2],sCam->view[1][2],sCam->view[2][2]));
			model.draw();
			break;
		}
		case ShadowMap:
			model.program = Programs.get("depthShader");
			model.program->uniform("modelViewProjectionMatrix")->set(sCam->projection*sCam->view*fullTransform);
			model.draw();
			break;
	}
}
