#include "Tracer.h"


///Class' constructor requiring the sphere and
/// light source's values to create new Sphere class objects
Tracer::Tracer(const glm::vec3& _spherePosition, const float& _sphereRadius, const glm::vec3& _sphereColor,
	const glm::vec3& _lightPosition, const float& _lightRadius, const glm::vec3& _lightColor)
{
	///Create a new sphere for both the visible sphere and light source
	/// setting relevant values
	sphere = Sphere(_spherePosition, _sphereRadius, _sphereColor);
	light = Sphere(_lightPosition, _lightRadius, _lightColor);
}


///Set the sphere's position
void Tracer::setSpherePosition(const glm::vec3& _spherePosition)
{
	sphere.center = _spherePosition;
}

///Set the sphere's radius
void Tracer::setSphereRadius(const float& _sphereRadius)
{
	sphere.radius = _sphereRadius;
}

///Set the sphere's color
void Tracer::setSphereColor(const glm::vec3& _sphereColor)
{
	sphere.color = _sphereColor;
}


///Set the light source's position
void Tracer::setLightPosition(const glm::vec3& _lightPosition)
{
	light.center = _lightPosition;
}

///Set the light source's radius
void Tracer::setLightRadius(const float& _lightRadius)
{
	light.radius = _lightRadius;
}

///Set the light source's color
void Tracer::setLightColor(const glm::vec3& _lightColor)
{
	light.color = _lightColor;
}


///Function which calculates EACH pixel within the given dimensions(_sectionRect)
/// The _pixelData returns with the calculated values
void Tracer::createScene(std::vector<std::vector<glm::ivec3>>& _pixelData,
	const SDL_Rect& _sectionRect, const int& _choice)
{
	float t = 0.0f;
	///The blue sky's color fall off
	float horizon = 2.5f;

	///For each row of the given section
	for (int y = _sectionRect.y; y < _sectionRect.h; y++)
	{
		///For each column of the given section
		for (int x = _sectionRect.x; x < (_sectionRect.w + (_sectionRect.w * _choice)); x++)
		{
			///Create a temporary storage (RGB) : (Black)
			glm::ivec3 curPixelColor(0, 0, 0);

			///Creat a Ray object at current screen position, direction(forward)
			Ray ray(glm::vec3(x, y, 0), glm::vec3(0, 0, 1));

			///If the ray intersects/hits the sphere
			if (sphere.raySphereIntersection(ray, t))
			{
				///Calulate the color of the current pixel hitting the sphere
				/// Using the pixel's direction,
				/// the sphere's surface's angle
				///  Against the light source
				glm::vec3 pi = ray.origin + ray.direction * t;
				curPixelColor = glm::ivec3((sphere.color + white *
					(glm::dot((glm::normalize(light.center - pi)), (glm::normalize(sphere.getNormal(pi)))))) * 0.5);

				///Set the current position's _pixelData to the (clamped = 0-255)color
				_pixelData[y][x] = glm::clamp(curPixelColor, 0, 255);
			}
			///If the ray DOEN'T hit the sphere
			else
			{
				///Calculate the sky's blue to white falloff effect
				curPixelColor = skyColor + ((glm::vec3(1, 1, 1) * y) / horizon);
				///Set the current position's _pixelData to the (clamped = 0-255)color
				_pixelData[y][x] = glm::clamp(curPixelColor, 0, 255);
			}
		}
	}
}