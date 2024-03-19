#pragma once
#include "Window.h"
#include "MyTimer.h"
#include "ImGuiManager.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"

class App
{
public:
	App();
	// master frame / message loop
	int Go();
	~App();
private:
	void DoFrame();
	void ShowImguiDemoWindow();
	void test(int, int);
private:
	bool showDemoWindow{ false };
	ImGuiManager imgui;
	float speedFactor{1.f};
	Camera cam;
	std::unique_ptr<PointLight> pLight;
	Window wnd;
	MyTimer timer;
	Model nano{ wnd.Gfx(), "Models\\nano_textured\\nanosuit.obj" };
	Model nano2{ wnd.Gfx(), "Models\\nano_textured\\nanosuit.obj" };
};

