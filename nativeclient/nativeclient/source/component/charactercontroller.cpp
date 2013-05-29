#include "component/charactercontroller.h"
#include "base/entity.h"
#include "component/input.h"

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
}

void CharacterController::OnDeInit()
{
}









}