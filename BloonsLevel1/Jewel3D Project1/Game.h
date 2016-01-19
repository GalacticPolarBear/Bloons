#pragma once
#include "Alien.h"

#include <Jewel_Entity/Entity.h>
#include <Jewel_Rendering/RenderGroup.h>
#include <Jewel_Rendering/RenderPass.h>
#include <Jewel_Resource/ResourceLibrary.h>
#include <Jewel_Resource/ShaderData.h>
#include <Jewel_Resource/ConfigTable.h>


using namespace Jwl;

class Game
{
public:
	Game(ConfigTable &config);
	~Game();

	bool Init();
	void Exit();

	void Update(float deltaTime);
	void Draw();

	/* Rendering */
	RenderGroup MainGroup;
	RenderPass MainRenderPass;
	
	/* Scene */
	Entity MainCamera;
	Entity RootNode;
	Entity AlienSprite;
	
	/* Assets */
	ResourceLibrary AssetLoader;
	ConfigTable &Config;

private:

};
