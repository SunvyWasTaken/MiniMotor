#pragma once

#include "IRender.h"
#include "Setting.h"

#include <string>

class Console : public IDraw<Console>
{
	using type = std::string[GRID_SIZE_X + 1][GRID_SIZE_Y + 1];

public:

	void Init();

	void HandleEvent();

	void Draw() const;

	bool IsWindowOpen();

	void ClearWindow();

	void BufferFrame(size_t index, class IEntity* targetEntity);

	void CloseWindow();

private:

	struct MyContainer
	{
		static MyContainer* GetValue();

		static MyContainer* SelfPtr;

		static void DestroyContainer();

		type m_Image;

		int i = 0;

	private:
		MyContainer() {}
		MyContainer(const MyContainer&) = delete;
		MyContainer& operator=(const MyContainer&) = delete;
	};
};

using ConsoleDraw = IDraw<Console>;
