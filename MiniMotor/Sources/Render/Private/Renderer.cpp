#include "Renderer.h"

#include "VertexArray.h"
#include "OpenGLShader.h"

namespace
{
	struct SceneData
	{
		glm::mat4 ViewMatrix;
		glm::mat4 ProjectionMatrix;
	};

	SceneData m_SceneData;
}


namespace Sunset
{
	void Renderer::BeginScene(Camera& m_camera)
	{
		m_SceneData.ViewMatrix = m_camera.GetViewMatrice();
		m_SceneData.ProjectionMatrix = m_camera.GetProjection();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<ShaderOGL>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Use();
		shader->SetMatrice4("view", m_SceneData.ViewMatrix);
		shader->SetMatrice4("projection", m_SceneData.ProjectionMatrix);
		shader->SetMatrice4("model", glm::mat4(1.f));
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}