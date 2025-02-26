#pragma once

#include "RenderCommand.h"

namespace Sunset
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static Render::Type GetAPI() { return RendererApi::GetAPI(); }

	};
}
