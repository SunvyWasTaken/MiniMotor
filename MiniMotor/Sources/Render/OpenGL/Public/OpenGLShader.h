#pragma once

namespace Sunset
{
	class MM_API ShaderOGL
	{
	public:

		ShaderOGL(const std::string& vertPath, const std::string& fragPath);

		virtual ~ShaderOGL();

		void Use();

		void Set1I(const std::string& target, const int value);

		void Set1F(const std::string& target, const float value);

		void SetVec3F(const std::string& target, const glm::vec3& value);

		void SetMatrice4(const std::string& target, const glm::mat4& value);

	private:

		unsigned int _id;
	};
}
