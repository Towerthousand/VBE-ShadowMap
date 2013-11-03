#include "ShadowMapContainer.hpp"
#include "ShadowModel.hpp"
#include "Camera.hpp"

ShadowMapContainer::ShadowMapContainer() : depthBuffer(NULL) {
	setName("smc");
	depthBuffer = new RenderTarget();
	depthBuffer->attachTexture(SCRWIDTH,SCRHEIGHT,RenderTarget::DEPTH,Texture::DEPTH_COMPONENT,2);
	depthBuffer->getAttachedTexture(RenderTarget::DEPTH)->setFilter(GL_LINEAR,GL_LINEAR);
	depthBuffer->noDrawingTargets();
	RenderTarget::bindScreen();
}

ShadowMapContainer::~ShadowMapContainer() {
}

void ShadowMapContainer::draw() const {
	std::vector<const ShadowModel*> targets;
	this->getAllObjectsOfType<ShadowModel>(targets);
	//DEPTH BUFFER
	depthBuffer->use();
	glClear(GL_DEPTH_BUFFER_BIT);
	for(unsigned int i = 0; i < targets.size(); ++i)
		targets[i]->drawMode = ShadowModel::ShadowMap;
	ContainerObject::draw();
	//REAL DRAWING
	RenderTarget::bindScreen();
	for(unsigned int i = 0; i < targets.size(); ++i)
		targets[i]->drawMode = ShadowModel::Real;
	ContainerObject::draw();
}

Texture*ShadowMapContainer::getDepthTexture() {
	return depthBuffer->getAttachedTexture(RenderTarget::DEPTH);
}
