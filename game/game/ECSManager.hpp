#ifndef GAMEIMPL_ECSMANAGER_HPP
#define GAMEIMPL_ECSMANAGER_HPP

#include <vector>
#include <variant>
#include <memory>

#include "engine/Defines.hpp"
#include "game/Entity.hpp"
#include "game/Components.hpp"

using std::vector;
using std::shared_ptr;

class ECSManager 
{
public:
	void UpdateScene(f32 dt);
	void DrawScene();
	void PrepareDraw();

	u64 CreateEntity();
	void RemoveEntity(u64 entityId);
	Entity& FindEntity(u64 entityId);

	Transform2D& CreateTransform2DComponent(u64 entityId);
	Sprite& CreateSpriteComponent(u64 entityId, const str& texName);
	Rigidbody2D& CreateRigidbody2DComponent(u64 entityId, const Vector2& pos, const Rectangle& box);
	Input& CreateInputComponent(u64 entityId);

	template<class T>
	T& GetComponent(u64 entityId) {
		if constexpr (std::is_same_v<T, Transform2D>) {
			return transforms.at(FindEntityComponent(entityId, ComponentIndex::Transform2D));
		}
		else if constexpr (std::is_same_v<T, Sprite>) {
			return sprites.at(FindEntityComponent(entityId, ComponentIndex::Sprite));
		}
		else if constexpr (std::is_same_v<T, Rigidbody2D>) {
			return bodies.at(FindEntityComponent(entityId, ComponentIndex::Rigidbody2D));
		}
		else if constexpr (std::is_same_v<T, Input>) {
			return inputs.at(FindEntityComponent(entityId, ComponentIndex::Input));
		}
	}

private:

	static u64 maxId;

	// Entities and components
	vector<u64> entityIds;
	vector<Entity> entities;
	vector<u64> entitiesToRemove{};

	vector<Transform2D> transforms;
	vector<Sprite> sprites;
	vector<Rigidbody2D> bodies;
	vector<Input> inputs;

	i32 FindEntityComponent(u64 entityId, ComponentIndex componentIndex);

	void UpdateEntityWithComponent(u64 entityId, i32 newComponentId, ComponentIndex componentIndex);
	void CleanRemovedEntities();

	void SystemPhysicsUpdate(f32 dt);
	void SystemSpriteDraw();
	void SystemInputUpdate(f32 dt);


	template<class T>
	void RemoveComponent(vector<T>& components, Entity& removedEntity, ComponentIndex componentTypeIndex) {
		i32 typeIndex = static_cast<i32>(componentTypeIndex);
		auto componentIndex = removedEntity.components.at(typeIndex);
		if (componentIndex != -1) {
			auto last = components.end() - 1;
			FindEntity(last->entityId).components[typeIndex] = componentIndex;
			auto removedComponent = components.begin() + componentIndex;
			std::iter_swap(removedComponent, last);
			components.pop_back();
		}
	}

	template<class T>
	void RemoveEntityComponent(u64 entityId) {
		auto& removedEntity = FindEntity(entityId);
		if constexpr (std::is_same_v<T, Transform2D>) {
			RemoveComponent<Transform2D>(transforms, removedEntity, ComponentIndex::Transform2D);
		}
		else if constexpr (std::is_same_v<T, Sprite>) {
			RemoveComponent<Sprite>(sprites, removedEntity, ComponentIndex::Sprite);
		}
		else if constexpr (std::is_same_v<T, Rigidbody2D>) {
			RemoveComponent<Rigidbody2D>(bodies, removedEntity, ComponentIndex::Rigidbody2D);
		}
		else if constexpr (std::is_same_v<T, Input>) {
			RemoveComponent<Input>(inputs, removedEntity, ComponentIndex::Input);
		}
	}

};
#endif //GAMEIMPL_ECSMANAGER_HPP