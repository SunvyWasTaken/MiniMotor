#pragma once

class ShaderOGL
{
public:

	ShaderOGL(const std::string& vertPath, const std::string& fragPath);

	virtual ~ShaderOGL();

	void Use();

private:

	unsigned int _id;
};
