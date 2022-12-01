#pragma once
///Include the basic glm functions/data types
#include <glm.hpp>


///A all-public class holding both
/// Origin Point (x, y, z)
/// Direction	 (x, y, z)
struct Ray
{
public:
	///Contains THIS Ray's origin point on the screen
	glm::vec3 origin{ 0.0f, 0.0f, 0.0f };
	///Contains the direction THIS Ray is pointing
	glm::vec3 direction{ 0.0f, 0.0f, 0.0f };

public:
	///Constructor - Parameters needed are both Origin, and Direction to call
	Ray(const glm::vec3& _origin, const glm::ivec3& _direction)
		: origin(_origin), direction(_direction) { }
};