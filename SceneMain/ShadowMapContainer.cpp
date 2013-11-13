#include "ShadowMapContainer.hpp"
#include "ShadowModel.hpp"
#include "Camera.hpp"

ShadowMapContainer::ShadowMapContainer() : depthBuffer(nullptr) {
	setName("smc");

	depthBuffer = new RenderTarget(SCRWIDTH/4, SCRHEIGHT/4);
	depthBuffer->addTexture(RenderTarget::DEPTH, Texture::DEPTH_COMPONENT);
	depthBuffer->build();

	depthBuffer->getTextureForAttachment(RenderTarget::DEPTH)->setFilter(GL_LINEAR,GL_LINEAR);
	depthBuffer->getTextureForAttachment(RenderTarget::DEPTH)->setComparison(GL_LESS);
	RenderTarget::bind(nullptr);
}

ShadowMapContainer::~ShadowMapContainer() {
	delete depthBuffer;
}

void ShadowMapContainer::draw() const {
	std::vector<const ShadowModel*> targets;
	this->getAllObjectsOfType<ShadowModel>(targets);

	//DEPTH BUFFER
	RenderTarget::bind(depthBuffer);
	glViewport(0, 0, depthBuffer->getWidth(), depthBuffer->getHeight());
	glClear(GL_DEPTH_BUFFER_BIT);
	for(unsigned int i = 0; i < targets.size(); ++i)
		targets[i]->drawMode = ShadowModel::ShadowMap;
	ContainerObject::draw();

	//REAL DRAWING
	RenderTarget::bind(nullptr);
	glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
	for(unsigned int i = 0; i < targets.size(); ++i)
		targets[i]->drawMode = ShadowModel::Real;
	ContainerObject::draw();
}

Texture*ShadowMapContainer::getDepthTexture() {
	return depthBuffer->getTextureForAttachment(RenderTarget::DEPTH);
}
