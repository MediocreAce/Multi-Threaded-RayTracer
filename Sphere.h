#pragma once
///Includes baisc GLM data types and functions
#include <glm.hpp>
///Use of creating Ray struct objects
#include "Ray.h"


///Sphere class used to hold spherical data,
/// the position, radius, and color,
///  and a function to caluclate if a ray has HIT the sphere's surface
struct Sphere
{
public:
	///The (x,y,z) positon of the sphere's center
	glm::vec3 center{ 0.0f, 0.0f, 0.0f };
	///The radius of the sphere
	float radius = 0.0f;
	///The color of the sphere
	glm::vec3 color{ 0.0f, 0.0f, 0.0f };

public:
	///Default Constructor - Empty
	Sphere() { }
	///Constructor with values to iniailise THIS sphere's position, radius, and color
	Sphere(const glm::vec3& _spherePosition, const float& _sphereRadius, const glm::vec3& _sphereColor)
		: center(_spherePosition), radius(_sphereRadius), color(_sphereColor) { }

	///Function returns if the given ray has HIT the sphere's surface or not
	bool raySphereIntersection(const Ray& _ray, float& _t);

	///Get the normal of the surface,
	/// at the hit point's position
	glm::vec3 getNormal(glm::vec3 pi);
};