#pragma once
///Includes use of std::vector (storage of a single data type)
#include <vector>

///Includes basic SDL type and functions
#include <SDL.h>
///Includes basic GLM types and functions
#include <glm.hpp>
///Includes other GLM types and functions
#include <ext.hpp>

///Include ability to create a Sphere class object
#include "Sphere.h"
///Include ability to create a Ray struct object
#include "Ray.h"


///Class contains ability to create a Sphere, and a light source
/// ability to draw each pixel within a given dimension SDL_Rect(x, y, w, z)
class Tracer
{
private:
	///The color of White(RGB)
	glm::vec3 white{ 255, 255, 255 };
	///The color of the sky(RGB) : (Sky Blue)
	glm::vec3 skyColor{ 70, 215, 255 };

	///The visible sphere
	Sphere sphere;
	///The light source
	Sphere light;

public:
	///Delete the Default Constructor,
	/// as it should only be called WITH values passed-by
	Tracer() = delete;
	///Class' constructor requiring the sphere and
	/// light source's values to create new Sphere class objects
	Tracer(const glm::vec3& _spherePosition, const float& _sphereRadius, const glm::vec3& _sphereColor,
		const glm::vec3& _lightPosition, const float& _lightRadius, const glm::vec3& _lightColor);

	///Set the sphere's position
	void setSpherePosition(const glm::vec3& _spherePosition);
	///Set the sphere's radius
	void setSphereRadius(const float& _sphereRadius);
	///Set the sphere's color
	void setSphereColor(const glm::vec3& _sphereColor);

	///Set the light source's position
	void setLightPosition(const glm::vec3& _lightPosition);
	///Set the light source's radius
	void setLightRadius(const float& _lightRadius);
	///Set the light source's color
	void setLightColor(const glm::vec3& _lightColor);

	///Function which calculates EACH pixel within the given dimensions(_sectionRect)
	/// The _pixelData returns with the calculated values
	void createScene(std::vector<std::vector<glm::ivec3>>& _pixelData,
		const SDL_Rect& _sectionRect, const int& choice);
};