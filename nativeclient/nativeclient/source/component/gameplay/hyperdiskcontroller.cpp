#include "component/gameplay/hyperdiskcontroller.h"

#include "base/entity.h"
#include "component/glmanager.h"
#include "component/input.h"
#include "component/transform.h"
#include "component/glmanager.h"
#include "component/camera.h"
#include "component/spritermanager.h"
#include "component/spriteranimator.h"
#include "component/gameplay/diskcontroller.h"


#include "entity/player.h"

#include "base/kernel.h"

#include <glm/gtx/fast_trigonometry.hpp>

namespace Natorium
{

HyperdiskController::HyperdiskController()
	: m_currentDisk(nullptr)
{
}

HyperdiskController::~HyperdiskController()
{
}

void HyperdiskController::OnInit()
{

}

void HyperdiskController::OnTick(const natU64 _dt)
{
	Input* input = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<Input>();
	Transform* transform = GetEntity()->GetComponent<Transform>();
	RigidBody* rigidbody = GetEntity()->GetComponent<RigidBody>();

	glm::vec3 impulse(0.f);
	if(input->IsAction(Input::forward))
	{
		//transform->m_pos.y -= 0.1f*_dt;
		impulse.y = -1.f * _dt;
	}
	if(input->IsAction(Input::backward))
	{
		//transform->m_pos.y += 0.1f*_dt;
		impulse.y = 1.f * _dt;
	}
	if(input->IsAction(Input::left))
	{
		//transform->m_pos.x -= 0.1f*_dt;
		impulse.x = -1.f * _dt;
	}
	if(input->IsAction(Input::right))
	{
		//transform->m_pos.x += 0.1f*_dt;
		impulse.x = 1.f * _dt;
	}
	if(input->IsAction(Input::shoot1))
	{
		glm::vec2 mouse_pos;
		input->GetMousePosition(mouse_pos);
		Camera* camera = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>()->GetCamera();
		glm::vec3 world_pos = camera->GetPosScreenToWorld(mouse_pos);

		ShootDisk(world_pos);
	}
	if(input->IsAction(Input::jump))
	{
		SpriterAnimator* animator = GetEntity()->GetComponent<SpriterAnimator>();
		const struct scml_sprite_t* sprite = animator->GetSpriteSource();
		static animationMap_t::const_iterator it = sprite->m_animations.begin();
		
		++it;
		if(it == sprite->m_animations.end())
		{
			it = sprite->m_animations.begin();
		}
		
		animator->Play(it->second.m_name.c_str());
	}

	if(impulse.x != 0.f || impulse.y != 0.f)
	{
		rigidbody->ApplyLinearImpulse(impulse);
	}


	glm::vec2 mouse_pos;
	input->GetMousePosition(mouse_pos);
	glm::vec3 mouse_vec3(mouse_pos, 0.f);

	LookAtScreen(mouse_vec3);
}

void HyperdiskController::OnDeInit()
{
}

void HyperdiskController::ShootDisk(glm::vec3& _pos)
{
	if(m_currentDisk)
	{
		// move disk in front of me
		Transform* transform = m_currentDisk->GetEntity()->GetComponent<Transform>();
		Shape* shape = GetEntity()->GetComponent<RigidBody>()->GetShape();

		transform->m_pos = GetEntity()->GetComponent<Transform>()->GetPos();

		glm::vec3 forward = _pos - transform->GetPos();
		forward = glm::normalize(forward);

		glm::vec2 size = shape->GetSize();
		transform->m_pos.x += size.x * forward.x;
		transform->m_pos.y += size.y * forward.y;

		m_currentDisk->GetEntity()->SetEnabled(true);

		m_currentDisk->ShootAt(_pos);
		m_currentDisk = nullptr;
	}
}

void HyperdiskController::LookAtScreen(glm::vec3& _look)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	Camera* camera = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>()->GetCamera();

	glm::vec2 screen_pos = camera->GetPosWorldToScreen(transform->GetPos());

	//camera->GetPosScreenToWorld(glm::vec2(10, 10));


	natF32 vector_x = screen_pos.x - _look.x;
	natF32 vector_y = screen_pos.y - _look.y;

	//glm::vec3 screen(screen_pos.x, screen_pos.y, 0.f);
	//transform->m_rad.z = glm::fastAtan(vector_y, vector_x);
	glm::vec3 euler(0.f);
	euler.z = std::atan2(vector_y, vector_x);

	transform->m_rot = glm::quat(euler);

	RigidBody* rigidbody = GetEntity()->GetComponent<RigidBody>();
	rigidbody->SetAngle(transform->m_rot);
}

void HyperdiskController::OnEnterCollide(Contact* _contact)
{
	Entity* B = static_cast<Entity*>(_contact->B->GetBody()->GetUserData());

	DiskController* diskcontroller = B->GetComponent<DiskController>();
	if(diskcontroller && m_currentDisk == nullptr)
	{
		B->SetEnabled(false);
		m_currentDisk = diskcontroller;
	}
}




}