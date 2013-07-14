#include "component/gameplay/aicontroller.h"

#include "base/entity.h"
#include "base/component.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "component/transform.h"
#include "component/rigidbody.h"

#include "component/gameplay/spawned.h"

#include <cassert>

namespace Natorium
{

AiController::AiController()
	: m_playersManager(nullptr)
	, m_lifeController(nullptr)
	, m_speed(0.1f)
{
}

AiController::~AiController()
{
}

void AiController::OnInit()
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	m_center = transform->GetPos();
	m_radius = 200.0f;
	m_t = 0.0f;

	m_playersManager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<PlayersManager>();
	m_lifeController = GetEntity()->GetComponent<LifeController>();

	assert(m_playersManager);
	assert(m_lifeController);
}

void AiController::OnTick(const natU64 _dt)
{
	if(!m_lifeController->IsAlive())
	{
		// called spawner first
		//m_spawner->OnKilled(GetEntity());

		Spawned* spawned = GetEntity()->GetComponent<Spawned>();
		assert(spawned);
		spawned->Kill();
	}
	else
	{
		// move toward player
		Entity* player = m_playersManager->GetLocalPlayer();
		Transform* transform_player = player->GetComponent<Transform>();
		Transform* transform = GetEntity()->GetComponent<Transform>();
		RigidBody* rigidbody = GetEntity()->GetComponent<RigidBody>();

		glm::vec3 direction = transform_player->GetPos() - transform->GetPos();

		if(direction != glm::vec3(0.f))
		{
			direction = glm::normalize(direction);
			//transform->m_pos += static_cast<natF32>(_dt) * direction * m_speed;
			direction = static_cast<natF32>(_dt) * direction;
			rigidbody->ApplyLinearImpulse(direction);

		}
	}
}

void AiController::OnDeInit()
{
	m_playersManager = nullptr;
	m_lifeController = nullptr;
}


}