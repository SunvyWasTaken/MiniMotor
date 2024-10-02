
#pragma once

#include "BaseSlate.h"

class SlateContainer
{
	using SlateList = std::vector<SContainer*>;
public:

	SlateContainer();
	~SlateContainer();

	void PushLayer(SContainer* slate);
	void PopLayer(SContainer* slate);

	SlateList::iterator begin() { return m_Slates.begin(); }
	SlateList::iterator end() { return m_Slates.end(); }

private:
	SlateList m_Slates;
	SlateList::iterator m_LayerInsert;
};
