#include <TinyEngine.h>
#include <TinyEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace TinyEngine {

	// TinyEditor¿‡ ºÃ≥– Application¿‡
	class TinyEditor : public Application
	{
	public:
		TinyEditor()
			: Application("Tiny Editor")
		{
			PushLayer(new EditorLayer());
		}

		~TinyEditor()
		{
		}
	};

	Application* CreateApplication()
	{
		return new TinyEditor();
	}

}