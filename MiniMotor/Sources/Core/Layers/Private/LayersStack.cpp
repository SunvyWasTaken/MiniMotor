#include "LayersStack.h"

namespace Sunset
{
	LayerStack::LayerStack()
		: m_LayerInsert(m_Layers.begin())
	{

	}

	LayerStack::~LayerStack()
	{
		for (auto it : m_Layers)
		{
			delete it;
		}
	}

	//void LayerStack::PopLayer(Layer* layer)
	//{
	//	auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
	//	if (it != m_Layers.end())
	//	{
	//		m_Layers.erase(it);
	//		m_LayerInsert--;
	//		layer->OnDetach();
	//	}
	//}

	//void LayerStack::PopOverlay(Layer* overlay)
	//{
	//	auto it = std::find(m_Layers.begin(), m_Layers.end(), overlay);
	//	if (it != m_Layers.end())
	//	{
	//		m_Layers.erase(it);
	//		overlay->OnDetach();
	//	}
	//}

}