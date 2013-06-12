#include "component/gameplay/civilianai.h"

#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"

namespace Natorium
{

CivilianAI::CivilianAI()
{
}

CivilianAI::~CivilianAI()
{
}

void CivilianAI::OnInit()
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	m_center = transform->GetPos();
	m_radius = 200.0f;
	m_t = 0.0f;

	transform->m_pos.x = m_center.x + m_radius*glm::cos(m_t);
	transform->m_pos.y = m_center.y + m_radius*glm::sin(m_t);
}

void CivilianAI::OnTick(const natU64 _dt)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();

	m_t += 0.1f * _dt / m_radius;

	transform->m_pos.x = m_center.x + m_radius*glm::cos(m_t);
	transform->m_pos.y = m_center.y + m_radius*glm::sin(m_t);
}

void CivilianAI::OnDeInit()
{

}




}