#include "tepch.h"
#include "Scene.h"

#include "Components.h"
#include "TinyEngine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace TinyEngine {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	// 右键选择创建一个Entity的时候，会配置一个初始的TransformComponent 和 TagComponent
	Entity Scene::CreateEntity(const std::string& name)
	{
		// m_Registry.create() 用于创建一个entity, entt::entity其实是uint32_t
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	// 销毁一个Entity
	void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

	// 实时更新这个 Scene
	void Scene::OnUpdateRuntime(Timestep ts)
	{
		// Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				// TODO: Move to Scene::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);
			});
		}

		// Render 2D
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			// 获取所有带有TransformComponent和CameraComponent的entity数组
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto[transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}

		if (mainCamera)
		{
			// 重新写了一个BeginScene
			Renderer2D::BeginScene(*mainCamera, cameraTransform);

			// group用来获取同时满足拥有多个Component的Entity数组, 这里得到的group是
			// m_Registry里所有既有TransformComponent又有SpriteRendererComponent的Entity数组
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
			for (auto entity : group)
			{
				auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

				// 重新写了一个DrawQuad
				Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
			}

			Renderer2D::EndScene();
		}
	}

	// 实时更新这个 Editor Scene
	void Scene::OnUpdateEditor(Timestep ts, EditorCamera& camera)
	{
		// 重新写了一个BeginScene
		Renderer2D::BeginScene(camera);

		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto[transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform.GetTransform(), sprite.Color);
		}

		Renderer2D::EndScene();
	}

	void Scene::OnViewportResize(uint32_t width, uint32_t height)
	{
		m_ViewportWidth = width;
		m_ViewportHeight = height;

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(width, height);
		}

	}

	Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{ entity, this };
		}
		return {};
	}

	template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		static_assert(false);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}

	template<>
	void Scene::OnComponentAdded<SpriteRendererComponent>(Entity entity, SpriteRendererComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}
}