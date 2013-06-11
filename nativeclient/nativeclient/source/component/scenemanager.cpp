#include "component/scenemanager.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "entity/player.h"
#include "entity/civilian.h"

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
	Entity* player = new Player();
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, player);

	Entity* dummy_ai = new Civilian();
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, dummy_ai);

	Entity* camera_dummy = new Entity();
	camera_dummy->AddComponent<Transform>();
	camera_dummy->AddComponent<Camera>();
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, camera_dummy);

	Camera* camera = player->GetComponent<Camera>();
	Transform* transform = player->GetComponent<Transform>();
	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();

	//transform->m_pos.x = 400;
	//transform->m_pos.y = 200;
	glmanager->SetCamera(camera);
}

void SceneManager::OnTick(const natU64 _dt)
{

}

void SceneManager::OnDeInit()
{

}










}