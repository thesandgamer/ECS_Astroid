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
	srand((unsigned)time(0));

	i32 sceneId = ToSceneId(SceneName::SceneGame);


	//==========] Load Textures [==========//
	AssetsManager::LoadTexture("Ship", "../game/asset/Ship.png", sceneId);
	AssetsManager::LoadTexture("ShipWithThrust", "../game/asset/ShipWithThrust.png", sceneId);
	AssetsManager::LoadTexture("Astroid", "../game/asset/Astroid.png", sceneId);
	AssetsManager::LoadTexture("Laser", "../game/asset/Laser.png", sceneId);

	
	//==========] Astroids [==========//
	u64 astroid = ecs->CreateEntity(); //Entit� vaisseau
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
		//astroidRB.angularVelocity = 1.0f; //Si rajoute �a �a plante
	}

	//==========] SHIP [==========//
	u64 ship = ecs->CreateEntity(); //Entit� vaisseau
	Transform2D& shipTrsf = ecs->CreateTransform2DComponent(ship);
	shipTrsf.pos = { 400,400 };

	Sprite& shipSprite = ecs->CreateSpriteComponent(ship, "Ship");
	Rectangle& shipCollisionBoxSize = shipSprite.srcRect;
	Rigidbody2D& shipRB = ecs->CreateRigidbody2DComponent(ship, shipTrsf.pos, shipCollisionBoxSize);
	Shooting& shipShoot = ecs->CreateShootingComponent(ship, 1);


	Input& shipInput = ecs->CreateInputComponent(ship);

	//==========] Projectile [==========// ?????
	//Trouver comment bien d�truire les entit�s et remove leurs components
	//Cr�er un component shooting: pour permettre de tirer des projectiles
	//Cr�er un component life manager: pour prendre des damages et g�rer sa vie
	//Cr�er un component damages maker: pour faire des damages

	u64 laser = ecs->CreateEntity(); //Entit� vaisseau
	Transform2D& laserTrsf = ecs->CreateTransform2DComponent(laser);
	laserTrsf.pos = { 400,400 };
	Sprite& laserSprite = ecs->CreateSpriteComponent(laser, "Laser");
	Rectangle& laserCollisionBoxSize = laserSprite.srcRect;
	Rigidbody2D& laserRB = ecs->CreateRigidbody2DComponent(laser, laserTrsf.pos, laserCollisionBoxSize);
	laserRB.forwardVelocity = 40;

	//ecs->RemoveEntity(laser);

	
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