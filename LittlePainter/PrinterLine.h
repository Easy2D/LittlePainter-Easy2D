#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

class PrinterLine
	:public Sprite
{
public:
	void onUpdate()override;

private:
	Point StartPoint;
	bool isJustPressed = false;

	Shape* CurrentShape = nullptr;
	ShapeNode* lastShapeNode = nullptr;
};