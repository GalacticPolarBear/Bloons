#pragma once
#include "Grid.h"
#include "Alien.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "Tower.h"
#include "Bullet.h"
#include "Purchasable.h"
#include<algorithm>
#include <Jewel_Entity/Entity.h>
#include <Jewel_Rendering/RenderGroup.h>
#include <Jewel_Rendering/RenderPass.h>
#include <Jewel_Resource/ResourceLibrary.h>
#include <Jewel_Resource/ShaderData.h>
#include <Jewel_Resource/ConfigTable.h>
#include <Jewel_OS\EventManager.h>
#include <Jewel_OS/Windows/Console.h>
#include <Jewel_Input/InputKeyboard.h>
#include <Jewel_Utilities/Logging.h>
#include <Jewel_Utilities/Rendering.h>
#include <Jewel_Sound/SoundSystem.h>
#include <Jewel_Entity/Components/Camera.h>
#include <Jewel_Entity/Components/Material.h>
#include <Jewel_Entity/Components/Sprite.h>
#include <Jewel_Entity/Components/Text.h>
#include <Jewel_Rendering\Primitives.h>
#include <Jewel_Utilities\Math.h>

using namespace Jwl;



class Game : public EventListener
{
public:
	Game(ConfigTable &config);
	~Game();

	bool Init();
	void Exit();

	void Update(float deltaTime);
	void Draw();
	
	virtual void EventCallBack(EventData *e);
	
	void MakeAlienWave(int num, int spacing, Path& path);
	
	Entity* MakeBullet(Entity *);

	Entity* MakeTower(BuildType);
	
	bool CheckTower();

	/*Internal*/
	Grid GameGrid;
	
	/* Rendering */
	RenderGroup MainGroup;
	RenderPass MainRenderPass;
		
	/*Object Construction*/
	Texture SpriteTexture;
	Shader SpriteShader;
	
	Texture ProjTexture;
	Shader ProjShader;

	Texture TowerRed;
	Texture TowerBlue;

	Shader TowerShader;

	/* Scene */
	Entity MainCamera;
	Entity RootNode;
	Entity MousePosText;
	Entity GameBG;
	Entity GoldText;
	Entity HealthText;
	Entity Tower1;
	Entity Tower2;
	Entity Square1;
	Entity Square2;

	Entity * ToBuild = NULL;

	CollisionManager CollManager;

	std::vector<Entity *> UI;

	/* Assets */
	ResourceLibrary AssetLoader;
	ConfigTable &Config;

	int PlayerGold = 300;
	int PlayerHealth = 100;
	int numBullets = 0;
	bool BuildMode = false;
	bool CanPlaceTower = false;

private:

};
