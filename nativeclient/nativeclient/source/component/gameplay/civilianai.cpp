#include "component/gameplay/civilianai.h"

#include "base/entity.h"
#include "base/component.h"
#include "component/transform.h"

#include "base/kernel.h"
#include "base/layer.h"

namespace Natorium
{

CivilianAI::CivilianAI()
	: m_sceneManager(nullptr)
	, m_speed(0.1f)
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

	m_sceneManager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<SceneManager>();
}

void CivilianAI::OnTick(const natU64 _dt)
{
	//Transform* transform = GetEntity()->GetComponent<Transform>();

	//m_t += 0.1f * _dt / m_radius;

	//transform->m_pos.x = m_center.x + m_radius*glm::cos(m_t);
	//transform->m_pos.y = m_center.y + m_radius*glm::sin(m_t);

	// move toward player
	Entity* player = m_sceneManager->GetLocalPlayer();
	Transform* transform_player = player->GetComponent<Transform>();
	Transform* transform = GetEntity()->GetComponent<Transform>();

	glm::vec3 direction = transform_player->GetPos() - transform->GetPos();

	if(direction != glm::vec3(0.f))
	{
		direction = glm::normalize(direction);
		transform->m_pos += static_cast<natF32>(_dt) * direction * m_speed;
	}


}

void CivilianAI::OnDeInit()
{
	m_sceneManager = nullptr;
}




}