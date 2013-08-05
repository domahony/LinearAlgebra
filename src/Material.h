/*
 * Material.h
 *
 *  Created on: 2013-08-04
 *      Author: domahony
 */

#ifndef MATERIAL_H_
#define MATERIAL_H_

namespace domahony {
namespace framework {

class Material {
public:
	Material(const glm::vec3& specular_color, const float& gloss) :
		specular_color(specular_color), gloss(gloss) {
	}

	void set_specular_color(const glm::vec3& v) {
		specular_color = v;
	}

	void set_gloss(const float& gloss) {
		this->gloss  = gloss;
	}

	glm::vec3 get_specular_color() const {
		return specular_color;
	}

	float get_gloss() const {
		return gloss;
	}

	virtual ~Material() {

	}

private:
	glm::vec3 specular_color;
	float gloss;

};

} /* namespace framework */
} /* namespace domahony */
#endif /* MATERIAL_H_ */
