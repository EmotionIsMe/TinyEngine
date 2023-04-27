#pragma once

#include "Scene.h"

namespace TinyEngine {

	// 序列化的顺序按范围从大到小，先是Scene，再是Entity，然后是Component
	class SceneSerializer
	{
	public:
		SceneSerializer(const Ref<Scene>& scene);

		void Serialize(const std::string& filepath);
		void SerializeRuntime(const std::string& filepath);

		bool Deserialize(const std::string& filepath);
		bool DeserializeRuntime(const std::string& filepath);
	private:
		Ref<Scene> m_Scene;
	};

}