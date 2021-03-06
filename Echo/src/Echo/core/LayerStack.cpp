#include "LayerStack.h"

// push layer to top
void Echo::LayerStack::push_to_top(const std::string& name)
{
	for (int i = 0; i < layerStack.size(); i++)
	{
		if (layerStack[i]->GetLayerName() == name)
		{
			layerStack.push_back(std::move(layerStack[i]));
			return;
		}
	}
	LOG_warning(name + " not found");
}

// swap layers
void Echo::LayerStack::swap(const std::string& layer1, const std::string& layer2)
{
	int layer1Index = -1, layer2Index = -1;
	for (int i = 0; i < layerStack.size(); i++)
	{
		if (layerStack[i]->GetLayerName() == layer1)
			layer1Index = i;
		else if (layerStack[i]->GetLayerName() == layer2)
			layer2Index = i;
	}
	if (layer1Index == -1)
	{
		LOG_warning(layer1 + " not found");
	}
	else if (layer2Index == -1)
	{
		LOG_warning(layer2 + " not found");
	}
	else
	{
		auto temp = layerStack[layer1Index];
		layerStack[layer1Index] = layerStack[layer2Index];
		layerStack[layer2Index] = temp;
	}
	return;
}