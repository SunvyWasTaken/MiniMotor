#include "Renderer.h"

#include "VertexArray.h"
#include "OpenGLShader.h"

namespace
{
	struct SceneData
	{
		glm::mat4 ViewProjectionMatrix;
	};

	SceneData m_SceneData;
}


namespace Sunset
{
	void Renderer::BeginScene(Camera& m_camera)
	{
		m_SceneData.ViewProjectionMatrix = m_camera.GetViewMatrice();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<ShaderOGL>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Use();
		shader->SetMatrice4("view", m_SceneData.ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}