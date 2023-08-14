#include "tepch.h"
#include "Scene.h"

#include "Components.h"
#include "TinyEngine/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

// Box2D
#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_polygon_shape.h"

namespace TinyEngine {

    static b2BodyType Rigidbody2DTypeToBox2DBody(Rigidbody2DComponent::BodyType bodyType)
    {
        switch (bodyType)
        {
        case Rigidbody2DComponent::BodyType::Static:    return b2_staticBody;
        case Rigidbody2DComponent::BodyType::Dynamic:   return b2_dynamicBody;
        case Rigidbody2DComponent::BodyType::Kinematic: return b2_kinematicBody;
        }

        TE_CORE_ASSERT(false, "Unknown body type");
        return b2_staticBody;
    }

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

    void Scene::OnRuntimeStart()
    {
		// 1.创建一个物体世界/环境
        m_PhysicsWorld = new b2World({ 0.0f, -9.8f });

		// 1.1为当前场景所有具有物理组件的实体创建b2Body
        auto view = m_Registry.view<Rigidbody2DComponent>();
        for (auto e : view)
        {
            Entity entity = { e, this };
            auto& transform = entity.GetComponent<TransformComponent>();
            auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();
			
			// 2.1 主体定义用来指定动态类型和参数
            b2BodyDef bodyDef;
            bodyDef.type = Rigidbody2DTypeToBox2DBody(rb2d.Type);
            bodyDef.position.Set(transform.Translation.x, transform.Translation.y);
            bodyDef.angle = transform.Rotation.z;

			// 2.2 由b2BodyDef创建主体
            b2Body* body = m_PhysicsWorld->CreateBody(&bodyDef);
            body->SetFixedRotation(rb2d.FixedRotation);
            rb2d.RuntimeBody = body;

            if (entity.HasComponent<BoxCollider2DComponent>())
            {
                auto& bc2d = entity.GetComponent<BoxCollider2DComponent>();
				
				// 3.1定义盒子包围盒
                b2PolygonShape boxShape;
                boxShape.SetAsBox(bc2d.Size.x * transform.Scale.x, bc2d.Size.y * transform.Scale.y);
				
				// 3.2定义fixture，fixture包含定义的包围盒
                b2FixtureDef fixtureDef;
                fixtureDef.shape = &boxShape;
                fixtureDef.density = bc2d.Density;
                fixtureDef.friction = bc2d.Friction;
                fixtureDef.restitution = bc2d.Restitution;
                fixtureDef.restitutionThreshold = bc2d.RestitutionThreshold;
				// 3.3定义主体的fixture
                body->CreateFixture(&fixtureDef);
            }
        }
    }

    void Scene::OnRuntimeStop()
    {
        delete m_PhysicsWorld;
        m_PhysicsWorld = nullptr;
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

        // Physics
        {
			// 脚本影响pyhsic然后渲染，当前帧得到结果
            const int32_t velocityIterations = 6;
            const int32_t positionIterations = 2;
            m_PhysicsWorld->Step(ts, velocityIterations, positionIterations);

            // Retrieve transform from Box2D
            auto view = m_Registry.view<Rigidbody2DComponent>();
            for (auto e : view)
            {
                Entity entity = { e, this };
                auto& transform = entity.GetComponent<TransformComponent>();
                auto& rb2d = entity.GetComponent<Rigidbody2DComponent>();

				// 获取物理模拟计算后的主体
                b2Body* body = (b2Body*)rb2d.RuntimeBody;
				// 将计算后的值赋予实体
                const auto& position = body->GetPosition();
                transform.Translation.x = position.x;
                transform.Translation.y = position.y;
                transform.Rotation.z = body->GetAngle();
            }
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
				Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
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

			Renderer2D::DrawSprite(transform.GetTransform(), sprite, (int)entity);
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
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
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

    template<>
    void Scene::OnComponentAdded<Rigidbody2DComponent>(Entity entity, Rigidbody2DComponent& component)
    {
    }

    template<>
    void Scene::OnComponentAdded<BoxCollider2DComponent>(Entity entity, BoxCollider2DComponent& component)
    {
    }
}