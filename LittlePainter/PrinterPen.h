#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

class PrinterPen
	:public Sprite
{
public:
	void onUpdate()override;

private:
	Point _lastPoint = { 0,0 };

	bool _isJustPressed = false;
};