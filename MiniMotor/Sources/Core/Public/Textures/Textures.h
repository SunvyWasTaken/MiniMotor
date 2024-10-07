// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"

template <typename Derived>
class MM_EXPORT TextureManager
{
public:

	static TextureManager<Derived>* GetInstance()
	{
		static Derived instance;
		return &instance;
	}

	CRTP_CALL_Variadic(Derived, LoadTexture)
	CRTP_CALL_Variadic_ret(Derived, decltype(auto), GetTextures)
};

class Texture
{
public:
	std::string filename;
	IVec2 coord;
};
