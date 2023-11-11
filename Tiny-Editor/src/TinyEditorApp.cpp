#include <TinyEngine.h>
#include <TinyEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace TinyEngine {

	// TinyEditor¿‡ ºÃ≥– Application¿‡
	class TinyEditor : public Application
	{
	public:
		TinyEditor(const ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args)
	{
		ApplicationSpecification spec;
		spec.Name = "TinyEditor";
		spec.CommandLineArgs = args;

		return new TinyEditor(spec);
	}

}