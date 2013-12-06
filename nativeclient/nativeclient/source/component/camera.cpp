#include "component/camera.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "component/transform.h"
#include "component/glmanager.h"
#include "component/input.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Natorium
{

Camera::Camera()
	: m_viewMatrix(1.0f)
	, m_projectionMatrix(1.0f)
	, m_resolution(0, 0)
	, m_effect_followMouse(false)
	, m_efect_followMouseSmooth(0.15f)
{

}

Camera::~Camera()
{
}

void Camera::OnInit()
{
	m_resolution = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>()->GetScreenResolution();
	m_projectionMatrix = glm::ortho<natF32>(0.f, static_cast<float>(m_resolution.x), static_cast<natF32>(m_resolution.y), 0.f, 0.f, 100.f);

	m_transform = GetEntity()->GetComponent<Transform>();
	assert(m_transform);

	//hack .. does not work with multiple camera
	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>();
	glmanager->SetCamera(this);
}

void Camera::OnTick(const natU64 _dt)
{

}

void Camera::ComputeMatrix()
{
	m_viewMatrix = glm::mat4(1.f);

	glm::vec3 pos = GetPos();
	pos *= -1;
	m_viewMatrix = glm::translate(m_viewMatrix, pos);

	//glm::vec3 center(m_resolution.x / 2, m_resolution.y / 2, 0);
	//m_viewMatrix = glm::translate(m_viewMatrix, center);

	// TODO : refactor effect
	if(m_effect_followMouse)
	{
		ApplyEffectFollowMouse();
	}
}

void Camera::OnDeInit()
{
}


glm::vec3 Camera::GetPos()
{
	return m_transform->GetPos();
}

glm::quat Camera::GetRot()
{
	return m_transform->GetRot();
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
	//assert(false);
	glm::vec3 pos = GetPos();
	glm::vec3 world(0.f);

	world.x = pos.x - m_resolution.x / 2 + _screen.x;
	world.y = pos.y - m_resolution.y / 2 + _screen.y;

	return glm::vec3(world);
}


void Camera::ApplyEffectFollowMouse()
{
	Input* input = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<Input>();
	glm::vec2 mouse;
	input->GetMousePosition(mouse);

	glm::vec2 screen = GetPosWorldToScreen(GetPos());
	glm::vec2 diff = m_efect_followMouseSmooth*(screen - mouse);
	
	glm::vec3 diff_vec3(diff, 0.f);
	m_viewMatrix = glm::translate(m_viewMatrix, diff_vec3);
}


}