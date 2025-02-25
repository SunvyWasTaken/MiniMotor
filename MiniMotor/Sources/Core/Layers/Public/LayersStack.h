#pragma once

#include "Layers.h"

namespace Sunset
{
	class MM_API LayerStack final
	{
		using LayerList = std::vector<Layer*>;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer)
		{
			m_LayerInsert = m_Layers.emplace(m_LayerInsert, layer);
			layer->OnAttach();
		}

		template <typename TLayer, typename ...Args>
		void PushOverlay(Args&&... args)
		{
			m_Layers.emplace_back(std::make_unique<TLayer>(std::forward<Args>(args)...));
			(*(m_Layers.end() - 1))->OnAttach();
		}

		//void PopLayer(Layer* layer);
		//void PopOverlay(Layer* overlay);

		LayerList::iterator begin() { return m_Layers.begin(); }
		LayerList::iterator end() { return m_Layers.end(); }

	private:
		LayerList m_Layers;
		LayerList::iterator m_LayerInsert;
	};
}
