#include "component/charactercontroller.h"
#include "base/entity.h"
#include "component/input.h"
#include "component/transform.h"

#include <iostream>
#include <cmath>

namespace Natorium
{

CharacterController::CharacterController()
{
}

CharacterController::~CharacterController()
{
}

void CharacterController::OnInit()
{
}

void CharacterController::OnTick(natU64 _dt)
{
	Input* input = GetEntity()->GetComponent<Input>();

	if(input->IsAction(Input::forward))
	{
		printf("forward pressed\n");
	}
	if(input->IsAction(Input::backward))
	{
		printf("backward pressed\n");
	}


	glm::vec2 mouse_pos;
	input->GetMousePosition(mouse_pos);
	LookAtScreen(mouse_pos);
}

void CharacterController::OnDeInit()
{
}


void CharacterController::LookAtScreen(glm::vec2& _look)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();

	natF32 vector_x = transform->m_pos.x - _look.x;
	natF32 vector_y = transform->m_pos.y - _look.y;

	transform->m_rad.z = std::atan2(vector_y, vector_x);
}

void CharacterController::LookAtWorld(natF32 _x, natF32 _y, natF32 _z)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
}






}