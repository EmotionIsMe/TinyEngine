#include "tepch.h"
#include "Layer.h"

namespace TinyEngine {
	Layer::Layer(const std::string& debugName) 
		: m_DebugName(debugName)
	{
	}

	Layer:: ~Layer()
	{
	}
}
