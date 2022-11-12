#include "PrinterCircle.h"

void PrinterCircle::onUpdate()
{
	if (Input::isDown(MouseCode::Left))
	{
		auto MousePos = Input::getMousePos();
		if (isJustPressed)
		{
			if (MousePos.y > 110)
			{
				Vector2 radius = { abs((MousePos.x - StartPoint.x) / 2),abs((MousePos.y - StartPoint.y) / 2) };
				CurrentShape = Shape::createEllipse(Point((MousePos.x + StartPoint.x) / 2, (MousePos.y + StartPoint.y) / 2), radius);
				SceneManager::getCurrentScene()->removeChild(lastShapeNode);
				lastShapeNode = gcnew ShapeNode(CurrentShape);
			}
			else
			{
				isJustPressed = false;

				Vector2 radius = { abs((MousePos.x - StartPoint.x) / 2),abs((110 - StartPoint.y) / 2) };
			}
		}
		else
		{
			if (MousePos.y > 110)
			{
				isJustPressed = true;
				StartPoint = MousePos;

				Vector2 radius = { 0,0 };
				CurrentShape = Shape::createEllipse(StartPoint, radius);
				lastShapeNode = gcnew ShapeNode(CurrentShape);
				SceneManager::getCurrentScene()->addChild(lastShapeNode);
			}
		}
	}
	else
	{
		isJustPressed = false;
	}
}
