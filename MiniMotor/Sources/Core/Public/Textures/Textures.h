// Copyright Shimmer Studios : All rights reserved.

#pragma once

#include "CoreMinimal.h"

using TextureCoord = std::array<IVec2, 4>;

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

	Texture() = default;

	Texture(const std::string name, const TextureCoord& coords)
		: filename(name)
		, coord(coords)
	{
		
	}

	template <typename Sides>
	IVec2& GetCoord()
	{
		static_assert(IsTypeInList<Sides, QuadSide>::value, "Not a valid Side");
		return coord[GetTypelistIndex<Sides, QuadSide>::value];
	}

	std::string filename;
	TextureCoord coord;
};
