#ifndef PROP_HPP
#define PROP_HPP
#include "commons.hpp"

class Prop : public GameObject {
	public:
		enum Technique {
			ShadowMap = 0,
			Real
		};

		Prop(std::string meshID, std::string texId);

		void update(float deltaTime);
		void draw() const;

		vec3f pos;
		vec3f rot;
		vec3f scale;
	private:
		Texture* tex;
		mutable Model model;
		Technique drawMode;

	friend class ShadowMapContainer;
};

#endif // PROP_HPP
