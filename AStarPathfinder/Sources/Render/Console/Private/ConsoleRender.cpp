#include "ConsoleRender.h"

#include "Entitys.h"

#include <iostream>
#include <thread>
#include <Windows.h>

Console::MyContainer* Console::MyContainer::SelfPtr = nullptr;

void Console::Init()
{
	ClearWindow();
}

void Console::HandleEvent()
{
}

void Console::Draw() const
{
	for (size_t y = 0; y < GRID_SIZE_Y + 1; ++y)
	{
		for (size_t x = 0; x < GRID_SIZE_X + 1; ++x)
		{
			static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			std::cout.flush();
			COORD coord = { (SHORT)x, (SHORT)y };
			SetConsoleCursorPosition(hOut, coord);

			std::cout << (MyContainer::GetValue()->m_Image)[x][y];
		}
		std::cout << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
}

bool Console::IsWindowOpen()
{
	++MyContainer::GetValue()->i;
	return MyContainer::GetValue()->i < 100;
}

void Console::ClearWindow()
{
	for (size_t y = 0; y < GRID_SIZE_Y + 1; ++y)
	{
		for (size_t x = 0; x < GRID_SIZE_X + 1; ++x)
		{
			MyContainer::GetValue()->m_Image[x][y] = ' ';
		}
	}
}

void Console::BufferFrame(size_t index, IEntity* targetEntity)
{
	if (targetEntity)
	{
		(MyContainer::GetValue()->m_Image)[targetEntity->Location.x][targetEntity->Location.y] = targetEntity->Character;
	}
}

void Console::CloseWindow()
{
	MyContainer::DestroyContainer();
}

Console::MyContainer* Console::MyContainer::GetValue()
{
	if (!SelfPtr)
	{
		SelfPtr = new MyContainer();
	}
	return SelfPtr;
}

void Console::MyContainer::DestroyContainer()
{
	delete SelfPtr;
}
