#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

#include "MenuBar.h"

// ����ֱ�߲����ṹ��  
struct LinePara
{
	float k;
	float b;
};

// ��ȡֱ�߲���  
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
