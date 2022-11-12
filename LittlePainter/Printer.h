#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

#include "MenuBar.h"

// 定义直线参数结构体  
struct LinePara
{
	float k;
	float b;
};

// 获取直线参数  
LinePara GetLinePara(Point p1, Point p2);

Point GetInLinePoint(float y, LinePara LP);

class Printer
	:public Scene
{
public:
	Printer();

	void onUpdate()override;

	Sprite* GetToolSprite(MenuBar::PrintTool tool);

private:
	MenuBar::PrintTool CurrentTool;
	Sprite* Tool;
};
