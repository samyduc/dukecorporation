#include "component/charactercontroller.h"
#include "base/entity.h"
#include "component/input.h"
#include "component/transform.h"
#include "component/glmanager.h"
#include "component/camera.h"

#include "base/kernel.h"

#include <iostream>

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

void CharacterController::OnTick(const natU64 _dt)
{
	Input* input = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<Input>();

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
	glm::vec3 mouse_vec3(mouse_pos, 0.f);

	LookAtScreen(mouse_vec3);
}

void CharacterController::OnDeInit()
{
}


void CharacterController::LookAtScreen(glm::vec3& _look)
{
	Transform* transform = GetEntity()->GetComponent<Transform>();
	Camera* camera = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>()->GetCamera();

	glm::vec2 screen_pos = camera->GetPosWorldToScreen(transform->GetPos());

	//camera->GetPosScreenToWorld(glm::vec2(10, 10));

	natF32 vector_x = screen_pos.x - _look.x;
	natF32 vector_y = screen_pos.y - _look.y;


	transform->m_rad.z = glm::atan(vector_y, vector_x);
}






}