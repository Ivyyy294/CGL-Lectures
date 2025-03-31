// include the basic windows header files and the Direct3D header file
#include "IvyyyEngine.h"
#include "IvyyySceneHandler.h"
#include "JonasScene.h"
#include "TreeScene.h"
#include "IvyyyScreen.h"
#include "IvyyyQuaternion.h"
#include "math.h"
#include "IvyyyWindow.h"
#include "D3DTestScene.h"

// the entry point for any Windows program
int WINAPI WinMain (HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	Ivyyy::Window::SetFullscreen(true);
	Ivyyy::Screen::SetResolution(Ivyyy::Resolution{1920, 1080});
	//Ivyyy::Renderer::SetMode(Renderer::Mode::DX11);
	//Ivyyy::SceneHandler::AddScene <D3DTestScene> ();

	//Ivyyy::SceneHandler::AddScene <TreeScene> ();
	Ivyyy::SceneHandler::AddScene <JonasScene> ();

	return Ivyyy::IvyyyEngine::Start (hInstance, nCmdShow);
}