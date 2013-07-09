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
	texturemanager->Load("/data/grass-texture-2.jpg");

	FontManager* fontmanager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<FontManager>();
	fontmanager->Load("/data/EBGaramond-Regular.ttf", 50);
	fontmanager->Load("/data/StalinistOne-Regular.ttf", 50);
	fontmanager->Load("/data/StalinistOne-Regular.ttf", 12);
	
	natU32 hash = Hash::Compute("/data/idle-0.png");
	GLuint textureId = texturemanager->Get(hash);
	natU32 hash_floor = Hash::Compute("/data/grass-texture-2.jpg");
	GLuint textureId_floor = texturemanager->Get(hash_floor);

	//
	Text* text = new Text();
	TextShape* text_shape = text->GetComponent<TextShape>();
	text_shape->m_font = fontmanager->Get("/data/StalinistOne-Regular.ttf", 50);
	text_shape->m_text = "Je suis espagnol";
	text_shape->m_color = glm::vec4(1.f, 0.f, 1.f, 1.f);
	Transform* text_transform = text->GetComponent<Transform>();
	text_transform->m_pos = glm::vec3(0.f, 0.f, 0.f);
	GLRender* text_render = text->GetComponent<GLRender>();
	text_render->SetTexture(text_shape->m_font->m_texture);

	GetEntity()->GetKernel()->AddEntity(Layer::Layer_5, text);

	//
	FPS* fps = new FPS();
	TextShape* fps_shape = fps->GetComponent<TextShape>();
	fps_shape->m_font = fontmanager->Get("/data/StalinistOne-Regular.ttf", 12);
	fps_shape->m_text = "1";
	fps_shape->m_color = glm::vec4(0.f, 0.f, 0.f, 1.f);
	Transform* fps_transform = fps->GetComponent<Transform>();
	fps_transform->m_pos = glm::vec3(100, 100.f, 0.f);
	GLRender* fps_render = fps->GetComponent<GLRender>();
	fps_render->SetTexture(fps_shape->m_font->m_texture);

	GetEntity()->GetKernel()->AddEntity(Layer::Layer_5, fps);

	//
	Floor* floor = new Floor();
	GLRender* floor_glrender = floor->GetComponent<GLRender>();
	floor_glrender->SetTexture(textureId_floor);
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, floor);

	//
	PlayersManager *playersManager = GetEntity()->GetKernel()->GetLayer(Layer::Layer_0)->GetRootEntity()->GetComponent<PlayersManager>();

	//
	Entity* player = new Player();
	Transform* player_transform = player->GetComponent<Transform>();
	//player_transform->m_pos = glm::vec3(612.f, 384.f, 0.f);
	player_transform->m_pos = glm::vec3(0.f, 0.f, 0.f);
	GLRender* player_glrender = player->GetComponent<GLRender>();
	player_glrender->SetTexture(textureId);

	GetEntity()->GetKernel()->AddEntity(Layer::Layer_2, player);
	playersManager->AddPlayer(player);

	//
	Entity* civilian = new Civilian();

	//
	SpawnerCivilian* spawner_civilian = new SpawnerCivilian();
	Transform *spawner_transform = spawner_civilian->GetComponent<Transform>();
	spawner_transform->m_pos = glm::vec3(-100.f, -100.f, 0.f);
	TimeSpawner* spawner1 = spawner_civilian->GetComponent<TimeSpawner>();
	spawner1->m_refEntity = civilian;
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner_civilian);

	//
	SpawnerCivilian* spawner_civilian2 = new SpawnerCivilian();
	Transform *spawner_transform2 = spawner_civilian2->GetComponent<Transform>();
	spawner_transform2->m_pos = glm::vec3(1024.f + 100.f, 0.f, 0.f);
	TimeSpawner* spawner2 = spawner_civilian2->GetComponent<TimeSpawner>();
	spawner2->m_refEntity = civilian;
	GetEntity()->GetKernel()->AddEntity(Layer::Layer_1, spawner_civilian2);

	//
	Camera* camera = player->GetComponent<Camera>();
	//Camera* camera = text->GetComponent<Camera>();
	camera->m_effect_followMouse = false;
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