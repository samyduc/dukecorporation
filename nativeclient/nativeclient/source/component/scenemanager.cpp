#include "component/scenemanager.h"
#include "base/kernel.h"

#include "entity/player.h"

namespace Natorium
{

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::OnInit()
{
	GetEntity()->GetKernel()->AddEntity(new Player());
}

void SceneManager::OnTick(natU64 _dt)
{

}

void SceneManager::OnDeInit()
{

}










}