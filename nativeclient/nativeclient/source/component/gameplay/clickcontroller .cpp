#include "component/gameplay/clickcontroller.h"

#include "base/entity.h"
#include "base/kernel.h"
#include "base/layer.h"
#include "base/component.h"

#include "component/spritermanager.h"
#include "component/spriteranimator.h"
#include "component/glmanager.h"
#include "component/camera.h"
#include "component/input.h"
#include "component/transform.h"
#include "component/shape.h"
#include "component/rigidbody.h"

#include <assert.h>

namespace Natorium
{

ClickController::ClickController()
	: m_speed(0.f)
	, m_worldTaget(0.f)
{
}

ClickController::~ClickController()
{
}

void ClickController::OnInit()
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	m_worldTaget = transform->GetPos();
}

void ClickController::OnDeInit()
{

}

void ClickController::OnTick(const natU64 _dt)
{
	Input* input = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<Input>();
	Transform* transform = GetEntity()->GetComponent<Transform>();
	SpriterAnimator* animator = GetEntity()->GetComponent<SpriterAnimator>();
	
	if(input->IsAction(Input::shoot1))
	{
		glm::vec2 mouse_pos;
		input->GetMousePosition(mouse_pos);
		Camera* camera = GetEntity()->GetKernel()->GetLayer(Layer::s_LayerManager)->GetRootEntity()->GetComponent<GLManager>()->GetCamera();
		glm::vec3 world_pos = camera->GetPosScreenToWorld(mouse_pos);

		m_worldTaget = world_pos;
	}

	natF32 move = m_speed.x * (6.f / _dt);

	glm::vec3 pos = transform->GetPos();
	if(pos.x == m_worldTaget.x)
	{
		// stop animation
		if(animator->GetCurrentAnimation() && animator->GetCurrentAnimation()->m_name != "idle")
		{
			animator->Play("idle");
		}
	}
	else
	{
		if(animator->GetCurrentAnimation() && animator->GetCurrentAnimation()->m_name != "walk")
		{
			animator->Play("walk");
		}

		if(pos.x - m_worldTaget.x > 0.f)
		{
			// left
			transform->m_pos.x -= move;
		}
		else
		{
			// right
			transform->m_pos.x += move;
		}

		if(glm::abs(transform->m_pos.x - m_worldTaget.x) < m_speed.x)
		{
			transform->m_pos.x = m_worldTaget.x;
		}
	}
}




}