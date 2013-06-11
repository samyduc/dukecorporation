#include "component/camera.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "component/transform.h"
#include "component/glmanager.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Natorium
{

Camera::Camera()
	: m_viewMatrix(1.0f)
	, m_projectionMatrix(1.0f)
	, m_resolution(640, 480)
{

}

Camera::~Camera()
{
}

void Camera::OnInit()
{
	glm::vec2 resolution = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>()->GetScreenResolution();

	m_projectionMatrix = glm::ortho<float>(0.f, static_cast<float>(resolution.x), static_cast<float>(resolution.y), 0.f, 0.f, 100.f);
}

void Camera::OnTick(const natU64 _dt)
{
	m_viewMatrix = glm::mat4(1.f);

	glm::vec3 pos = GetPos();
	pos *= -1;
	m_viewMatrix = glm::translate(m_viewMatrix, pos);

	//glm::vec3 center(m_resolution.x / 2, m_resolution.y / 2, 0);
	//m_viewMatrix = glm::translate(m_viewMatrix, center);
}

void Camera::OnDeInit()
{
}

glm::vec3 Camera::GetPos()
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	return transform->GetPos();

}

glm::vec3 Camera::GetDeg()
{
	Transform* transform = GetEntity()->GetComponent<Transform>();

	return transform->GetDeg();
}

glm::vec2 Camera::GetPosWorldToScreen(const glm::vec3& _world)
{
	glm::vec2 screen(0.f);
	//glm::vec4 temp(0.f);

	/*glm::mat4 projectionViewMatrix = m_projectionMatrix * m_viewMatrix;
	temp = projectionViewMatrix * glm::vec4(_world, 0.f);

	screen.x = glm::round( ((temp.x + 1) / 2.0f ) * m_resolution.x);
	screen.y = glm::round( ((1 - temp.y) / 2.0f ) * m_resolution.y);*/

	// hack ...
	glm::vec3 pos = GetPos();

	screen.x = -1 * (pos.x - m_resolution.x / 2 - _world.x);
	screen.y = -1 * (pos.y - m_resolution.y / 2 - _world.y);

	return screen;
}

glm::vec3 Camera::GetPosScreenToWorld(const glm::vec2& _screen)
{
	/*glm::vec4 temp(0.f);

	temp.x = 2.f * _screen.x / m_resolution.x - 1;
	temp.y = -2.f * _screen.y / m_resolution.y + 1;

	glm::mat4 viewProjectionInverseMatrix = glm::inverse(m_projectionMatrix * m_viewMatrix);
	glm::vec4 world = viewProjectionInverseMatrix * temp;*/

	// hack ... (not working)
	assert(false);
	glm::vec3 pos = GetPos();
	glm::vec3 world(0.f);

	world.x = pos.x - m_resolution.x / 2 - _screen.x;
	world.y = pos.y - m_resolution.y / 2 - _screen.y;

	return glm::vec3(world);
}

}