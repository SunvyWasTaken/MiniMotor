#pragma once

#include "RenderCommand.h"
#include "Camera.h"

namespace Sunset
{
	class ShaderOGL;

	class Renderer
	{
	public:
		static void BeginScene(Camera& m_camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<ShaderOGL>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static Render::Type GetAPI() { return RendererApi::GetAPI(); }
	};
}
