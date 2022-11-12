#include "PrinterPen.h"
#include "MenuBar.h"
#include "Printer.h"

void PrinterPen::onUpdate()
{
	if (Input::isDown(MouseCode::Left))
	{
		if (_isJustPressed)
		{
			auto MousePos = Input::getMousePos();
			if (MousePos != _lastPoint)
			{
				if(MousePos.y > MenuBar::GetMenuBarBottom() && _lastPoint.y > MenuBar::GetMenuBarBottom())
				{
					auto shape = Shape::createLine(_lastPoint, MousePos);
					auto SHAPE = gcnew ShapeNode(shape);
					//SHAPE->setPos(_lastPoint);
					SHAPE->setStrokeColor(MenuBar::GetStrokeCurrentColor());
					SceneManager::getCurrentScene()->addChild(SHAPE);
				}
				else if (MousePos.y > MenuBar::GetMenuBarBottom())
				{
					auto shape = Shape::createLine(MousePos,GetInLinePoint(MenuBar::GetMenuBarBottom(),GetLinePara(_lastPoint, MousePos)));
					auto SHAPE = gcnew ShapeNode(shape);
					//SHAPE->setPos(_lastPoint);
					SHAPE->setStrokeColor(MenuBar::GetStrokeCurrentColor());
					SceneManager::getCurrentScene()->addChild(SHAPE);
				}
				else if (_lastPoint.y > MenuBar::GetMenuBarBottom())
				{
					auto shape = Shape::createLine(_lastPoint, GetInLinePoint(MenuBar::GetMenuBarBottom(), GetLinePara(_lastPoint, MousePos)));
					auto SHAPE = gcnew ShapeNode(shape);
					//SHAPE->setPos(_lastPoint);
					SHAPE->setStrokeColor(MenuBar::GetStrokeCurrentColor());
					SceneManager::getCurrentScene()->addChild(SHAPE);
				}
			}
		}
		_isJustPressed = true;
		_lastPoint = Input::getMousePos();
	}
	else
	{
		_isJustPressed = false;
	}
}
