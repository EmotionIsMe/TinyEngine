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
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}