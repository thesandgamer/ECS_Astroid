#include "SceneGame.hpp"
#include "engine/AssetsManager.hpp"

SceneGame::SceneGame(shared_ptr<ECSManager> ecsRef,Game& game) : ecs{ std::move(ecsRef) }, game{ game }
{

}


void SceneGame::Load() 
{
	i32 sceneId = ToSceneId(SceneName::SceneGame);
	AssetsManager::LoadTexture("Ship", "game\\asset\\Ship.png", sceneId);

	//==========] SHIP [==========//
	u64 ship = ecs->CreateEntity(); //Entit� vaisseau
	Transform2D& shipTrsf = ecs->CreateTransform2DComponent(ship);
	shipTrsf.scale = { 1,1 };

	Sprite& shipSprite = ecs->CreateSpriteComponent(ship, "Ship");
	Rectangle& shipCollisionBoxSize = shipSprite.srcRect;
	Rigidbody2D& shipRB = ecs->CreateRigidbody2DComponent(ship, shipTrsf.pos, shipCollisionBoxSize);
	
}

void SceneGame::Update(f32 dt) 
{

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