#include <TinyEngine.h>

#include "imgui/imgui.h"

class ExampleLayer : public TinyEngine::Layer {

public:
	ExampleLayer()
		:Layer("Example") 
	{
	}
	
	void OnUpdate() override {
		//TE_INFO("ExampleLayer::Update");
		if (TinyEngine::Input::IsKeyPressed(TE_KEY_TAB))
			TE_TRACE("tap key is pressed (polling)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(TinyEngine::Event& event) override {

		if (event.GetEventType() == TinyEngine::EventType::KeyPressed){

			TinyEngine::KeyPressedEvent& e = (TinyEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == TE_KEY_TAB)
				TE_TRACE("Tab key is pressed (event)!");
			TE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};
class Sandbox : public TinyEngine::Application
{
public:
	Sandbox() {

		PushLayer(new ExampleLayer());
	}
	~Sandbox() {

	}

private:

};

TinyEngine::Application*  TinyEngine::CreateApplication() {
	
	return new Sandbox();
}
