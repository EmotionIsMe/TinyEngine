#pragma once

#include "TinyEngine/Core/Core.h"
#include "TinyEngine/Core/Log.h"
#include "TinyEngine/Scene/Scene.h"
#include "TinyEngine/Scene/Entity.h"

namespace TinyEngine {

	// SceneHierarchyPanel 把Scene里的Entity用Imgui绘制出来
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& scene);

		void SetContext(const Ref<Scene>& scene);

		void OnImGuiRender(); // 在EditorLayer里的OnImguiRender里调用它而已 

		Entity GetSelectedEntity() const { return m_SelectionContext; }
		void SetSelectedEntity(Entity entity);
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;  // 代表Selected Entity
	};

}