#include "PrinterLine.h"
#include "MenuBar.h"
#include "Printer.h"

void PrinterLine::onUpdate()
{
	if (Input::isDown(MouseCode::Left))
	{
		auto MousePos = Input::getMousePos();
		if (isJustPressed)
		{
			if (MousePos.y > MenuBar::GetMenuBarBottom())
			{
				CurrentShape = Shape::createLine(StartPoint,MousePos);
			}
			else
			{
				CurrentShape = Shape::createLine(StartPoint, GetInLinePoint(MenuBar::GetMenuBarBottom(),GetLinePara(StartPoint,MousePos)));
			}

			SceneManager::getCurrentScene()->removeChild(lastShapeNode);
			lastShapeNode = gcnew ShapeNode(CurrentShape);
			lastShapeNode->setStrokeColor(MenuBar::GetStrokeCurrentColor());
			SceneManager::getCurrentScene()->addChild(lastShapeNode);
		}
		else
		{
			if (MousePos.y > 110)
			{
				isJustPressed = true;

				StartPoint = MousePos;
				CurrentShape = Shape::createLine(StartPoint, MousePos);
				lastShapeNode = gcnew ShapeNode(CurrentShape);
				lastShapeNode->setStrokeColor(MenuBar::GetStrokeCurrentColor());
				SceneManager::getCurrentScene()->addChild(lastShapeNode);
			}
		}
	}
	else
	{
		isJustPressed = false;
	}
}