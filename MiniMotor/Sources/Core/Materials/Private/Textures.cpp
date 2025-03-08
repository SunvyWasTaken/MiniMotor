#include "Textures.h"

#include <glad/glad.h>

namespace Sunset
{
	void Texture::Bind()
	{
		if (!isValid)

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, id);
		glActiveTexture(GL_TEXTURE0);
	}

}
