#pragma once

#include "Maths.h"

class MM_API ShaderOGL
{
public:

	ShaderOGL(const std::string& vertPath, const std::string& fragPath);

	virtual ~ShaderOGL();

	void Use();

	void Set1I(const std::string& target, const int value);

	void Set1F(const std::string& target, const float value);

	void SetVec3F(const std::string& target, const FVec3& value);

	void SetMatrice4(const std::string& target, const FMat4& value);

private:

	unsigned int _id;
};
