#include "XYSystem.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	XYSystem game;
	game.Initialize(hInstance);
	game.Run();
	game.Finalize();

	return 0;
}
