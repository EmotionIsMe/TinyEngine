#include <TinyEngine.h>
#include <TinyEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace TinyEngine {

	// TinyEditor¿‡ ºÃ≥– Application¿‡
	class TinyEditor : public Application
	{
	public:
		TinyEditor(ApplicationCommandLineArgs args)
			: Application("TinyEditor", args)
		{
			PushLayer(new EditorLayer());
		}

		~TinyEditor()
		{
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		return new TinyEditor(args);
	}

}