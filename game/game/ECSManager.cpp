#include "ECSManager.hpp"
#include "raylib.h"
#include "engine/GMath.hpp"

u64 ECSManager::maxId = 0;

void ECSManager::UpdateScene(f32 dt) 
{
	SystemPhysicsUpdate(dt);
	SystemInputUpdate(dt);
}

void ECSManager::DrawScene() 
{
	SystemSpriteDraw();
	CleanRemovedEntities();
}

u64 ECSManager::CreateEntity() 
{
	u64 newId = maxId++;
	entityIds.emplace_back(newId);
	entities.emplace_back(newId);
	return newId;
}

Transform2D& ECSManager::CreateTransform2DComponent(u64 entityId) 
{
	i32 newComponentId = static_cast<i32>(transforms.size());
	transforms.emplace_back(entityId);
	UpdateEntityWithComponent(entityId, newComponentId, ComponentIndex::Transform2D);
	return transforms.back();
}

Sprite& ECSManager::CreateSpriteComponent(u64 entityId, const str& texName) 
{
	i32 newComponentId = static_cast<i32>(sprites.size());
	const Texture& tex = AssetsManager::GetTexture(texName);
	sprites.emplace_back(entityId, texName, static_cast<float>(tex.width), static_cast<float>(tex.height));
	UpdateEntityWithComponent(entityId, newComponentId, ComponentIndex::Sprite);
	return sprites.back();
}

Rigidbody2D& ECSManager::CreateRigidbody2DComponent(u64 entityId, const Vector2& pos,const Rectangle& box) 
{

	i32 newComponentId = static_cast<i32>(bodies.size());
	bodies.emplace_back(entityId, pos, box);
	UpdateEntityWithComponent(entityId, newComponentId, ComponentIndex::Rigidbody2D);
	return bodies.back();
}

Input& ECSManager::CreateInputComponent(u64 entityId)
{
	i32 newComponentId = static_cast<i32>(inputs.size());
	inputs.emplace_back(entityId);
	UpdateEntityWithComponent(entityId, newComponentId, ComponentIndex::Input);
	return inputs.back();
}

void ECSManager::UpdateEntityWithComponent(u64 entityId, i32 newComponentId, ComponentIndex componentIndex) 
{
	i32 iComponentIndex = static_cast<i32>(componentIndex);
	FindEntity(entityId).components[iComponentIndex] = newComponentId;

}

void ECSManager::SystemSpriteDraw() 
{
	for (auto& sprite : sprites) {
		Color colorAlpha{ 255, 255, 255, sprite.opacity };
		const auto& transform = GetComponent<Transform2D>(sprite.entityId);
		render::DrawSprite(sprite.tex, sprite.srcRect, sprite.dstRect,colorAlpha, transform.rotation * -RAD2DEG);
	}
#ifdef GDEBUG
	for (auto& body : bodies) {
		body.DrawDebug();
	}
#endif

}

#include <iostream>

void ECSManager::SystemInputUpdate(f32 dt)
{
	for (auto input : inputs)
	{

		auto& rb = GetComponent<Rigidbody2D>(input.entityId);
		auto& transform = GetComponent<Transform2D>(rb.entityId);

		float forwardSpeed = 0.0f;
		if (IsKeyDown(KEY_UP))
		{
			forwardSpeed += input.maxForwardSpeed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			forwardSpeed -= input.maxForwardSpeed;
		}
		rb.forwardVelocity = forwardSpeed;


		float angularSpeed = 0.0f;
		if (IsKeyDown(KEY_LEFT))
		{
			angularSpeed += input.maxAngularSpeed;
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			angularSpeed -= input.maxAngularSpeed;
		}

		if (!Maths::nearZero(angularSpeed))
		{
			transform.rotation = transform.rotation + angularSpeed * dt;
		}
		std::cout << angularSpeed << std::endl;

	}
}

void ECSManager::RemoveEntity(u64 entityId) 
{
	entitiesToRemove.push_back(entityId);
}

void ECSManager::CleanRemovedEntities() 
{
	for (auto entityId : entitiesToRemove) {
		// Transform
		RemoveEntityComponent<Transform2D>(entityId);
		// Sprites
		RemoveEntityComponent<Sprite>(entityId);
		// Rigidbodies
		RemoveEntityComponent<Rigidbody2D>(entityId);
		std::erase(entityIds, entityId);
		std::erase_if(entities, [=](Entity entity) {
			return entity.id == entityId;
			});
	}
	entitiesToRemove.clear();
}



Entity& ECSManager::FindEntity(u64 entityId) 
{
	auto itr = std::lower_bound(entityIds.begin(), entityIds.end(), entityId);
	return entities.at(std::distance(entityIds.begin(), itr));
}

i32 ECSManager::FindEntityComponent(u64 entityId, ComponentIndex componentIndex) 
{
	return FindEntity(entityId).components.at(static_cast<i32>(componentIndex));
}

void ECSManager::PrepareDraw() 
{
	// Update sprite positions
	for (auto& sprite : sprites) 
	{
		const auto& transform = GetComponent<Transform2D>(sprite.entityId);
		sprite.dstRect = { transform.pos.x, transform.pos.y, static_cast<float>(sprite.tex.width) * transform.scale.x, static_cast<float>(sprite.tex.height) * transform.scale.y};
	}
}

void ECSManager::SystemPhysicsUpdate(f32 dt)
{
	for (auto rb : bodies)
	{
		auto& transform = GetComponent<Transform2D>(rb.entityId);


		Vector2 forward = transform.GetForward();
		Vector2 newPos = transform.pos + transform.GetForward() * rb.forwardVelocity * dt;	//Move forward
		transform.pos = newPos;
		rb.pos = transform.pos;
		DrawRay({ {transform.pos.x,transform.pos.y,0 },{forward.x,forward.y,0 } }, GREEN);


		//transform.pos = { transform.pos.x + rb.velocity.x * dt, transform.pos.y + rb.velocity.y *dt };

	}
}