#pragma once

#include "RendererApi.h"

namespace Sunset
{
	class OpenGLRendererAPI : public RendererApi
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}