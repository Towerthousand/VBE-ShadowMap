#include "ShadowMapContainer.hpp"
#include "ShadowModel.hpp"
#include "Camera.hpp"

ShadowMapContainer::ShadowMapContainer() : depthBuffer(nullptr) {
	setName("smc");

	depthBuffer = new RenderTarget(SCRWIDTH, SCRHEIGHT);
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
	glClear(GL_DEPTH_BUFFER_BIT);
	for(unsigned int i = 0; i < targets.size(); ++i)
		targets[i]->drawMode = ShadowModel::ShadowMap;
	ContainerObject::draw();
	//REAL DRAWING
	RenderTarget::bind(nullptr);
	for(unsigned int i = 0; i < targets.size(); ++i)
		targets[i]->drawMode = ShadowModel::Real;
	ContainerObject::draw();
}

Texture*ShadowMapContainer::getDepthTexture() {
	return depthBuffer->getTextureForAttachment(RenderTarget::DEPTH);
}
