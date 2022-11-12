#include "PrinterRect.h"
#include "MenuBar.h"
#include "Printer.h"

void PrinterRect::onUpdate()
{
	if (Input::isDown(MouseCode::Left))
	{
		Point MousePos = Input::getMousePos();
		if (isJustPressed)
		{
			if (MousePos.y > MenuBar::GetMenuBarBottom())
			{
				CurrentShape = Shape::createRect(Rect(StartPoint, Size(MousePos.x - StartPoint.x, MousePos.y - StartPoint.y)));
			}
			else
			{
				CurrentShape = Shape::createRect(Rect(StartPoint, Size(MousePos.x - StartPoint.x, MenuBar::GetMenuBarBottom() - StartPoint.y)));
			}

			SceneManager::getCurrentScene()->removeChild(lastShapeNode);
			lastShapeNode = gcnew ShapeNode(CurrentShape);
			lastShapeNode->setStrokeColor(MenuBar::GetStrokeCurrentColor());
			lastShapeNode->setFillColor(MenuBar::GetFillCurrentColor());
			SceneManager::getCurrentScene()->addChild(lastShapeNode);

		}
		else
		{
			if (MousePos.y > 110)
			{
				StartPoint = MousePos;
				isJustPressed = true;
				CurrentShape = Shape::createRect(Rect(StartPoint, Size(0, 0)));
				lastShapeNode = gcnew ShapeNode(CurrentShape);
				lastShapeNode->setStrokeColor(MenuBar::GetStrokeCurrentColor());
				lastShapeNode->setFillColor(MenuBar::GetFillCurrentColor());
				SceneManager::getCurrentScene()->addChild(lastShapeNode);
			}
		}
	}
	else
	{
		isJustPressed = false;
	}
}
