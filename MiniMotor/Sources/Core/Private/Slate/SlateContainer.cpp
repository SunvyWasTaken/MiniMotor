#include "Slate/SlateContainer.h"

SlateContainer::SlateContainer()
{
}

SlateContainer::~SlateContainer()
{
}

void SlateContainer::PushLayer(SContainer* slate)
{
	m_Slates.emplace_back(slate);
}

void SlateContainer::PopLayer(SContainer* slate)
{
	//auto it = std::find_if(m_Slates.begin(), m_Slates.end(), [slate](const std::shared_ptr<Slate>& s) { return s.get() == slate; });
	//if (it != m_Slates.end())
	//{
	//	m_Slates.erase(it);
	//}
}
