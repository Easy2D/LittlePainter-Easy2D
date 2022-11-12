//---------------------------------------------------------
// 程序名称：GreedyMonster
// 作者：白马王子
// 依赖版本：Easy2D v2.1.12
// 项目类型：Win32 Application
//---------------------------------------------------------

#include <easy2d/easy2d.h>
using namespace easy2d;

#include "Printer.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (Game::init("Printer",1200,800))
	{
		auto scene = gcnew Printer;
		SceneManager::enter(scene);

		Game::start();
	}
	Game::destroy();

	return 0;
}
