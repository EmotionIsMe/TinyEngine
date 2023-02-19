#include <TinyEngine.h>

class ExampleLayer : public TinyEngine::Layer {

public:
	ExampleLayer()
		:Layer("Example") 
	{
	}
	
	void OnUpdate() override {
		TE_INFO("ExampleLayer::Update");
	}

	void OnEvent(TinyEngine::Event& event) override {
		TE_TRACE("{0}", event);
	}
};
class Sandbox : public TinyEngine::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new TinyEngine::ImGuiLayer());
	}
	~Sandbox() {

	}

private:

};

TinyEngine::Application*  TinyEngine::CreateApplication() {
	
	return new Sandbox();
}
