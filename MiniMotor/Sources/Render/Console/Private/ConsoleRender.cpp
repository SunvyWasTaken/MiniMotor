// Copyright Shimmer Studios : All rights reserved.

#include "ConsoleRender.h"

#include "ECS/Entitys.h"
//
//#define NOMINMAX
//#include <Windows.h>

void ConsoleRender::Init()
{
	ClearWindow();
}

void ConsoleRender::HandleEvents()
{
}

void ConsoleRender::Draw() const
{
	for (size_t y = 0; y < 40; ++y)
	{
		for (size_t x = 0; x < 80; ++x)
		{
			//static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			//std::cout.flush();
			//COORD coord = { (SHORT)x, (SHORT)y };
			//SetConsoleCursorPosition(hOut, coord);

			std::cout << (m_Image)[x * 80 + y];
		}
		std::cout << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(5));
}

bool ConsoleRender::IsWindowOpen()
{
	++i;
	return i < 100;
}

void ConsoleRender::ClearWindow()
{
	for (size_t y = 0; y < 40; ++y)
	{
		for (size_t x = 0; x < 80; ++x)
		{
			m_Image[x* 80 + y] = ' ';
		}
	}
}

void ConsoleRender::BufferFrame(const VertexArray2D& targetEntity)
{
	//if (targetEntity)
	//{
	//	(m_Image)[targetEntity->Location.x][targetEntity->Location.y] = targetEntity->Character;
	//}
}

void ConsoleRender::CloseWindow()
{

}
