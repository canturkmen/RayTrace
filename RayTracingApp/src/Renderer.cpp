#include "Renderer.h"
#include "Walnut/Random.h"


void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if (m_FinalImage->GetWidth() == width && m_FinalImage->GetHeight() == height)
			return;

		m_FinalImage->Resize(width, height);
	}
	else
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);


	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render()
{
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			glm::vec2 coordinates = { (float)x / (float)m_FinalImage->GetWidth(), (float)y / (float)m_FinalImage->GetHeight() }; // Maps the coordinates to 0 to 1
			coordinates = coordinates * 2.0f - 1.0f; // Map it to -1 to 1
			m_ImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coordinates);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::PerPixel(glm::vec2 coords)
{
	// Ray Equation : m + n * t
	// m: Ray origin
	// n: Ray direction

	glm::vec3 RayOrigin = { 0.0f, 0.0f, -2.0f };
	glm::vec3 RayDirection = { coords.x, coords.y, -1.0f };

	// Sphere Equation: (b^2)t^2 + (2ab)t + a^2-c 
	// a = ray origin
	// b = ray direction
	// t = hit distance
	// r = radius

	float Radius = 0.5f;
	float a = glm::dot(RayDirection, RayDirection);
	float b = 2.0f * glm::dot(RayOrigin, RayDirection);
	float c = glm::dot(RayOrigin, RayOrigin) - (Radius * Radius);

	float discriminant = (b * b) - (4 * a * c);

	if (discriminant >= 0.0f)
		return 0xffff00ff;

	return 0xff000000;
}
