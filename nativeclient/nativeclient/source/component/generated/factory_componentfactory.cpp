// Generated file : do not edit manually 


#include "component/componentfactory.h"

#include "base/component.h"
#include "base/entity.h"
#include "base/serializer.h"

#include "component/gameplay/lifecontroller.h"
#include "component/gameplay/aicontroller.h"
#include "component/transform.h"
#include "component/spriteranimator.h"
#include "component/camera.h"
#include "component/glmanager.h"
#include "component/componentfactory.h"
#include "component/gameplay/timespawner.h"
#include "component/spritermanager.h"
#include "component/charactercontroller.h"
#include "component/fontmanager.h"
#include "component/spriteranimatorslave.h"
#include "component/texturemanager.h"
#include "component/sdlinput.h"
#include "component/ui/fpscounter.h"
#include "component/glrender.h"
#include "component/gameplay/baseweapon.h"
#include "component/textshape.h"
#include "component/sdlrender.h"
#include "component/rigidbody.h"
#include "component/scenemanager.h"
#include "component/squareshape.h"
#include "component/gameplay/bulletcontroller.h"
#include "component/physicsmanager.h"
#include "component/gameplay/spawner.h"
#include "component/filemanager.h"
#include "component/prefabmanager.h"
#include "component/gameplay/spawned.h"
#include "component/gameplay/shotgunweapon.h"
#include "component/ui.h"
#include "component/sdlmanager.h"
#include "component/playersmanager.h"


namespace Natorium
{

void ComponentFactory::PopulateFactory()
{
	m_componentFactory[LifeController::GetType()] = new LifeController();
	m_componentFactory[AiController::GetType()] = new AiController();
	m_componentFactory[Transform::GetType()] = new Transform();
	m_componentFactory[SpriterAnimator::GetType()] = new SpriterAnimator();
	m_componentFactory[Camera::GetType()] = new Camera();
	m_componentFactory[GLManager::GetType()] = new GLManager();
	m_componentFactory[ComponentFactory::GetType()] = new ComponentFactory();
	m_componentFactory[TimeSpawner::GetType()] = new TimeSpawner();
	m_componentFactory[SpriterManager::GetType()] = new SpriterManager();
	m_componentFactory[CharacterController::GetType()] = new CharacterController();
	m_componentFactory[FontManager::GetType()] = new FontManager();
	m_componentFactory[SpriterAnimatorSlave::GetType()] = new SpriterAnimatorSlave();
	m_componentFactory[TextureManager::GetType()] = new TextureManager();
	m_componentFactory[SDLInput::GetType()] = new SDLInput();
	m_componentFactory[FPSCounter::GetType()] = new FPSCounter();
	m_componentFactory[GLRender::GetType()] = new GLRender();
	m_componentFactory[BaseWeapon::GetType()] = new BaseWeapon();
	m_componentFactory[TextShape::GetType()] = new TextShape();
	m_componentFactory[SDLRender::GetType()] = new SDLRender();
	m_componentFactory[RigidBody::GetType()] = new RigidBody();
	m_componentFactory[SceneManager::GetType()] = new SceneManager();
	m_componentFactory[SquareShape::GetType()] = new SquareShape();
	m_componentFactory[BulletController::GetType()] = new BulletController();
	m_componentFactory[PhysicsManager::GetType()] = new PhysicsManager();
	m_componentFactory[Spawner::GetType()] = new Spawner();
	m_componentFactory[FileManager::GetType()] = new FileManager();
	m_componentFactory[PrefabManager::GetType()] = new PrefabManager();
	m_componentFactory[Spawned::GetType()] = new Spawned();
	m_componentFactory[ShotgunWeapon::GetType()] = new ShotgunWeapon();
	m_componentFactory[UI::GetType()] = new UI();
	m_componentFactory[SDLManager::GetType()] = new SDLManager();
	m_componentFactory[PlayersManager::GetType()] = new PlayersManager();
}

}
