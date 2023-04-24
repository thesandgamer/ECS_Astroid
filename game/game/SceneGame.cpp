#include "SceneGame.hpp"
#include "engine/AssetsManager.hpp"

SceneGame::SceneGame(shared_ptr<ECSManager> ecsRef,Game& game) : ecs{ std::move(ecsRef) }, game{ game }
{

}

void SceneGame::Load() 
{

}

void SceneGame::Update(f32 dt) 
{

}

void SceneGame::Draw() 
{

}

void SceneGame::Unload() 
{
	AssetsManager::UnloadSceneTextures(ToSceneId(SceneName::SceneGame));
}