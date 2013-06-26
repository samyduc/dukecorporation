#include "component/scenemanager.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "entity/player.h"
#include "entity/civilian.h"
#include "entity/spawnercivilian.h"
#include "component/playersmanager.h"

#include "component/texturemanager.h"

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
	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<TextureManager>();
	texturemanager->Load("/data/idle-0.png");

	natU32 hash = Hash::Compute("/data/idle-0.png");
	GLuint textureId = texturemanager->Get(hash);

	PlayersManager *playersManager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<PlayersManager>();

	Entity* player = new Player();
	Transform* player_transform = player->GetComponent<Transform>();
	player_transform->m_pos = glm::vec3(612.f, 384.f, 0.f);
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_2, player);
	playersManager->AddPlayer(player);

	Entity* civilian = new Civilian();

	SpawnerCivilian* spawner_civilian = new SpawnerCivilian();
	Transform *spawner_transform = spawner_civilian->GetComponent<Transform>();
	spawner_transform->m_pos = glm::vec3(-100.f, -100.f, 0.f);
	TimeSpawner* spawner1 = spawner_civilian->GetComponent<TimeSpawner>();
	spawner1->m_refEntity = civilian;
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner_civilian);

	SpawnerCivilian* spawner_civilian2 = new SpawnerCivilian();
	Transform *spawner_transform2 = spawner_civilian2->GetComponent<Transform>();
	spawner_transform2->m_pos = glm::vec3(1024.f + 100.f, 0.f, 0.f);
	TimeSpawner* spawner2 = spawner_civilian2->GetComponent<TimeSpawner>();
	spawner2->m_refEntity = civilian;
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner_civilian2);

	Camera* camera = player->GetComponent<Camera>();
	camera->m_effect_followMouse = true;
	Transform* transform = player->GetComponent<Transform>();
	GLManager* glmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<GLManager>();

	glmanager->SetCamera(camera);
}

void SceneManager::OnTick(const natU64 _dt)
{

}

void SceneManager::OnDeInit()
{

}







}