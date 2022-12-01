#include "Sphere.h"


///Function returns if the given ray has HIT the sphere's surface or not
bool Sphere::raySphereIntersection(const Ray& _ray, float& _t)
{
	///Using 
	glm::vec3 oc = _ray.origin - center;
	float b = (float)(2 * glm::dot(oc, _ray.direction));
	float c = (float)(glm::dot(oc, oc) - radius * radius);
	float distToHit = (float)(b * b - 4 * c);

	///If distance < 0
	/// return NO HIT
	if (distToHit < 0)
		return false;

	///Calculate the distance the ray took
	/// to the first hit of the sphere's surface
	distToHit = sqrt(distToHit);
	_t = (float)(-b - distToHit);

	///Return HIT
	return true;
}


///Get the normal of the surface,
/// at the hit point's position
glm::vec3 Sphere::getNormal(glm::vec3 pi)
{
	///Calculate the normal then return
	glm::vec3 normal = glm::vec3(pi - center);
	normal /= radius;
	return normal;
}