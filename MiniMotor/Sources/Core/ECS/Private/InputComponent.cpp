#include "InputComponent.h"

#include <GLFW/glfw3.h>

namespace Sunset
{
	void InputComponent::Bind(int key, const CallbackFunction& func)
	{
		auto curr = functions.find(key);
		if (curr == functions.end())
		{
			functions.emplace(key, func);
		}
	}

	void InputComponent::OnEvent(const Events& even, float deltatime)
	{
		std::visit(Overloaded{
		[&](KeyEvent arg){
			auto curr = functions.find(arg.key);
			if (curr != functions.end())
			{
				(functions.at(arg.key))(deltatime);
			}
		},
		[&](MouseEvent arg){
			
		}
		}, even);
	}
}
