#pragma once

namespace Sunset
{
	class Layer;
	
	class LayerStack final
	{
		using LayerList = std::vector<Layer*>;
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		LayerList::iterator begin() { return m_Layers.begin(); }
		LayerList::iterator end() { return m_Layers.end(); }

	private:
		LayerList m_Layers;
		LayerList::iterator m_LayerInsert;
	};
}
