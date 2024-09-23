
#pragma once

#include "CoreMinimal.h"

class Texture
{
public:
	Texture();
	~Texture();

	void LoadTexture(const std::string& path);
};