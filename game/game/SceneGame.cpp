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
	u64 ship = ecs->CreateEntity(); //Entité vaisseau
	Transform2D& shipTrsf = ecs->CreateTransform2DComponent(ship);
	shipTrsf.pos = { 400,400 };
	shipTrsf.rotation = 2;

	Sprite& shipSprite = ecs->CreateSpriteComponent(ship, "Ship");
	Rectangle& shipCollisionBoxSize = shipSprite.srcRect;
	Rigidbody2D& shipRB = ecs->CreateRigidbody2DComponent(ship, shipTrsf.pos, shipCollisionBoxSize);
	//shipRB.velocity = { 40,40 };
	shipRB.forwardVelocity = 40;

	
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