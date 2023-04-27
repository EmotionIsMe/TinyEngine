#pragma once

#include <glm/glm.hpp>

namespace TinyEngine {

	class OrthographicCamera
	{
	public:
		// 构造函数, 由于正交投影下, 需要Frustum, 默认near为-1, far为1, 就不写了
		// 不过这个构造函数没有指定Camera的位置, 所以应该是默认位置
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		// 读写Camera的位置和朝向, 这些数据是用于设置View矩阵的
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		// 返回三个矩阵的接口, 这些数据用于设置Projection矩阵
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;				// 作为计算时的Cache

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };	// 正交投影的相机位置好像也不重要
		float m_Rotation = 0.0f;						// 正交投影下的相机只会有绕Z轴的旋转
	};

}