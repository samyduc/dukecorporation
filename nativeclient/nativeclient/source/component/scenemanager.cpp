#include "component/scenemanager.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "entity/player.h"
#include "entity/civilian.h"
#include "entity/spawnercivilian.h"

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

	SpawnerCivilian* spawner_civilian = new SpawnerCivilian();
	Transform *spawner_transform = spawner_civilian->GetComponent<Transform>();
	spawner_transform->m_pos = glm::vec3(0.f, 0.f, 0.f);
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner_civilian);

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