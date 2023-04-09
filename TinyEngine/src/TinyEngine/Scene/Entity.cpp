#include "tepch.h"
#include "Entity.h"

namespace TinyEngine {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}