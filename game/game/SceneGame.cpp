#include "SceneGame.hpp"
#include "engine/AssetsManager.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>


SceneGame::SceneGame(shared_ptr<ECSManager> ecsRef,Game& game) : ecs{ std::move(ecsRef) }, game{ game }
{

}


void SceneGame::Load() 
{
	i32 sceneId = ToSceneId(SceneName::SceneGame);

	AssetsManager::LoadTexture("Ship", "game\\asset\\Ship.png", sceneId);
	AssetsManager::LoadTexture("Astroid", "game\\asset\\Astroid.png", sceneId);

	//==========] SHIP [==========//
	u64 ship = ecs->CreateEntity(); //Entité vaisseau
	Transform2D& shipTrsf = ecs->CreateTransform2DComponent(ship);
	shipTrsf.pos = { 400,400 };

	Sprite& shipSprite = ecs->CreateSpriteComponent(ship, "Ship");
	Rectangle& shipCollisionBoxSize = shipSprite.srcRect;
	Rigidbody2D& shipRB = ecs->CreateRigidbody2DComponent(ship, shipTrsf.pos, shipCollisionBoxSize);


	Input& shipInput = ecs->CreateInputComponent(ship);


	//==========] Astroids [==========//
	
	
	u64 astroid = ecs->CreateEntity(); //Entité vaisseau
	Transform2D& astroidTrsf = ecs->CreateTransform2DComponent(astroid);
	astroidTrsf.pos = { 600,600 };
	astroidTrsf.rotation = 1;

	Sprite& astroidSprite = ecs->CreateSpriteComponent(astroid, "Astroid");
	Rectangle& astroidCollisionBoxSize = astroidSprite.srcRect;
	Rigidbody2D& astroidRB = ecs->CreateRigidbody2DComponent(astroid, astroidTrsf.pos, astroidCollisionBoxSize);
	astroidRB.forwardVelocity = 100;
	

	i32 maxAstroidsCount{ 500 };
	i16 maxXPos = 1280 * 0.9f;
	i16 maxYPos = 720 * 0.9f;

	i16 maxVelocity = 80;
	i16 minVelocity = 60;

	i16 maxRotation = 50;
	i16 minRotation = -50;

	// Spawn astroids
	for (i16 i = 0; i < maxAstroidsCount; i++) {
		// Random position
		float randXPos = (float)(rand() % maxXPos);
		float randYPos = (float)(rand() % maxYPos);
		Vector2 randPos = { randXPos, randYPos };

		// Random velocity
		float randVel = (float)(rand() % (maxVelocity - minVelocity)) + minVelocity;
		float randRot = (float)(rand() % (maxRotation - minRotation)) + minRotation;

		u64 astroid = ecs->CreateEntity();
		Transform2D& astroidTransform = ecs->CreateTransform2DComponent(astroid);
		astroidTransform.pos = randPos;

		Sprite& astroidSprite = ecs->CreateSpriteComponent(astroid, "Astroid");
		Rigidbody2D& astroidRb = ecs->CreateRigidbody2DComponent(astroid, Vector2{ 0, 0 }, astroidSprite.srcRect);
		astroidTransform.rotation = randRot;
		astroidRb.forwardVelocity = randVel;
	}


	
}

void SceneGame::Update(f32 dt) 
{
	ecs->UpdateScene(dt);
}

void SceneGame::Draw() 
{
	ecs->PrepareDraw();
	ecs->DrawScene();
}

void SceneGame::Unload() 
{
	AssetsManager::UnloadSceneTextures(ToSceneId(SceneName::SceneGame));
}