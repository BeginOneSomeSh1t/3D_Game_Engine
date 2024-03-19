#include "App.h"
#include <memory>
#include <algorithm>
#include "MyMath.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "Imgui/imgui.h"
#include "Delegate.h"
#include "VertexBuffer.h"


GDIPlusManager gdipm;



App::App()
	:
	wnd(1280, 720, L"The Happy Window")
{
	pLight = std::make_unique<PointLight>(wnd.Gfx());

	wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
	
	wnd.mouse.BindToMouseWheelUp([&](int, int) { cam.AddTravelSpeed(2.f); });
	wnd.mouse.BindToMouseWheelDown([&](int, int) { cam.SubtractTravelSpeed(2.f); });

}



int App::Go()
{
	while (true)
	{
		// process all messages pending but not to block
		if (const auto ecode = Window::ProcessMessages())
			//if return optional has value, means we're
			return *ecode;
		DoFrame();
	}
}

App::~App()
{
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speedFactor;
	wnd.Gfx().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.Gfx().SetCamera(cam.GetMatrix());


	pLight->Bind(wnd.Gfx(), cam.GetMatrix());

	nano.Draw(wnd.Gfx());
	pLight->Draw(wnd.Gfx());

	
	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
			continue;
		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRow();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRow();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		default:
			break;
		}
	}

	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
			cam.Translate({ 0.f, 0.f, dt });
		if (wnd.kbd.KeyIsPressed('A'))
			cam.Translate({ -dt, 0.f, 0.f });
		if (wnd.kbd.KeyIsPressed('S'))
			cam.Translate({ 0.f, 0.f, -dt });
		if (wnd.kbd.KeyIsPressed('D'))
			cam.Translate({ dt, 0.f, 0.f });
		if (wnd.kbd.KeyIsPressed('E'))
			cam.Translate({ 0.f,dt, 0.f });
		if (wnd.kbd.KeyIsPressed('Q'))
			cam.Translate({ 0.f, -dt, 0.f });
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
		if (!wnd.CursorEnabled())
			cam.Rotate((float)delta->x, (float)delta->y);

	ShowImguiDemoWindow();
	nano.ShowWindow();

	cam.SpawnControlWindow();
	pLight->SpawnControlWindow();
	

	// present
	wnd.Gfx().EndFrame();
}

void App::ShowImguiDemoWindow()
{
	if (showDemoWindow)
		ImGui::ShowDemoWindow(&showDemoWindow);
	
}








