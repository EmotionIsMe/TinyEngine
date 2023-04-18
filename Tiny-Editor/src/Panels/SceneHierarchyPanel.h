#pragma once

#include "TinyEngine/Core/Core.h"
#include "TinyEngine/Core/Log.h"
#include "TinyEngine/Scene/Scene.h"
#include "TinyEngine/Scene/Entity.h"

namespace TinyEngine {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}