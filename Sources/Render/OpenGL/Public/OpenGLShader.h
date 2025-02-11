#pragma once

#include "Maths.h"

class ShaderOGL
{
public:

	ShaderOGL(const std::string& vertPath, const std::string& fragPath);

	virtual ~ShaderOGL();

	void Use();

	void SetMatrice4(const std::string& target, const FMat4& value);

	void SetVec3F(const std::string& target, const FVec3& value);

private:

	unsigned int _id;
};
