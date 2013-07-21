#include "component/scenemanager.h"
#include "base/kernel.h"
#include "base/layer.h"

#include "entity/player.h"
#include "entity/civilian.h"
#include "entity/spawnercivilian.h"
#include "entity/floor.h"
#include "entity/text.h"
#include "entity/fps.h"
#include "component/playersmanager.h"
#include "component/glrender.h"
#include "component/texturemanager.h"
#include "component/fontmanager.h"
#include "component/prefabmanager.h"

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
	PrefabManager* prefabmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<PrefabManager>();

	TextureManager* texturemanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<TextureManager>();

	texturemanager->Load("/data/idle-0.png");
	texturemanager->Load("/data/grass-texture-2.jpg");

	FontManager* fontmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FontManager>();
	fontmanager->Load("/data/font/EBGaramond-Regular.ttf", 50);
	fontmanager->Load("/data/font/StalinistOne-Regular.ttf", 100);
	fontmanager->Load("/data/font/StalinistOne-Regular.ttf", 12);

	natU32 hash_text_100 = fontmanager->Compute("/data/font/StalinistOne-Regular.ttf", 100);
	natU32 hash_text_12 = fontmanager->Compute("/data/font/StalinistOne-Regular.ttf", 12);
	
	natU32 hash = Hash::Compute("/data/idle-0.png");
	GLuint textureId = texturemanager->Get(hash);
	natU32 hash_floor = Hash::Compute("/data/grass-texture-2.jpg");
	GLuint textureId_floor = texturemanager->Get(hash_floor);

	// prefabs
	Entity* text = prefabmanager->CreateFromType("/data/prefab/text.prefab");
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_5, text);

	Entity* fps = prefabmanager->CreateFromType("/data/prefab/fps.prefab");
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_5, fps);

	//Entity* floor = prefabmanager->CreateFromType("/data/prefab/floor.prefab");
	//GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, floor);

	//
	PlayersManager *playersManager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<PlayersManager>();

	Entity* player = prefabmanager->CreateFromType("/data/prefab/player.prefab");
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_2, player);
	playersManager->AddPlayer(player);

	//
	Entity* spawner1 = prefabmanager->CreateFromType("/data/prefab/spawnercivilian.prefab");
	Transform *t_spawner1 = spawner1->GetComponent<Transform>();
	t_spawner1->m_pos = glm::vec3(1024.f, 0.f, 0.f);
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner1);

	Entity* spawner2 = prefabmanager->CreateFromType("/data/prefab/spawnercivilian.prefab");
	Transform *t_spawner2 = spawner2->GetComponent<Transform>();
	t_spawner2->m_pos = glm::vec3(-100.0f, -100.f, 0.f);
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner2);

	//
	Camera* camera = player->GetComponent<Camera>();
	//Camera* camera = text->GetComponent<Camera>();
	//camera->m_effect_followMouse = false;
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