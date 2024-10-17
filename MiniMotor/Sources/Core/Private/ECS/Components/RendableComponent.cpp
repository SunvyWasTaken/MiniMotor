// Copyright Shimmer Studios : All rights reserved.

#include "ECS/Components/RendableComponent.h"

RendableComponent::RendableComponent(const Texture& textu)
	: texture(textu)
{
}

void RendableComponent::SetTextureCoord(const TextureCoord& coord)
{
	texture.coord = coord;
}
