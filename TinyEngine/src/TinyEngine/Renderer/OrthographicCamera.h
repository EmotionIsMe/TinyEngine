#pragma once

#include <glm/glm.hpp>

namespace TinyEngine {

	class OrthographicCamera
	{
	public:
		// ���캯��, ��������ͶӰ��, ��ҪFrustum, Ĭ��nearΪ-1, farΪ1, �Ͳ�д��
		// ����������캯��û��ָ��Camera��λ��, ����Ӧ����Ĭ��λ��
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		// ��дCamera��λ�úͳ���, ��Щ��������������View�����
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		// ������������Ľӿ�, ��Щ������������Projection����
		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;				// ��Ϊ����ʱ��Cache

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };	// ����ͶӰ�����λ�ú���Ҳ����Ҫ
		float m_Rotation = 0.0f;						// ����ͶӰ�µ����ֻ������Z�����ת
	};

}