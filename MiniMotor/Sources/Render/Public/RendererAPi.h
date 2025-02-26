#pragma once

namespace Sunset
{
	class VertexArray;

	class RendererApi
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static Render::Type& GetAPI() { return m_Api; };

	private:
		static Render::Type m_Api;
	};
}
