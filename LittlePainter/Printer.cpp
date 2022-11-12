#include "Printer.h"
#include <vector>

/*
* Printer�������ShapeNode�ຯ��
*	���ܣ�
*		��ShapeNode����ӵ�ShapeNodes�ʲ��ڽ��й���
* ����ʵ�֣�
*	 ǰ�᣺
*		�ĵ�ǰ�����ƻ���Ϊ���޻���
* ����СΪ��
*		�������ʲ�������ShapeNode
*		����ShapeNode������ԭ��������ı�ֵ
*		����С����
*		����ֵ���»���������˾�����ShapeNode������
*/

Printer::Printer()
{
	MenuBar::init(this);

	Tool = GetToolSprite(MenuBar::GetCurrentPrintTool());
	this->addChild(Tool);
	CurrentTool = MenuBar::GetCurrentPrintTool();
}

void Printer::onUpdate()
{
	if (MenuBar::GetCurrentPrintTool() == MenuBar::INIT)
	{
		MenuBar::init(this);
		this->removeChild(Tool);
		Tool = GetToolSprite(MenuBar::GetCurrentPrintTool());
		this->addChild(Tool);
		CurrentTool = MenuBar::GetCurrentPrintTool();
		return;
	}
	if (MenuBar::GetCurrentPrintTool() != CurrentTool)
	{
		switch (MenuBar::GetCurrentPrintTool())
		{
		case MenuBar::LINE:
			this->removeChild(Tool);
			Tool = GetToolSprite(MenuBar::LINE);
			this->addChild(Tool);
			CurrentTool = MenuBar::LINE;
			break;
		case MenuBar::RECT:
			this->removeChild(Tool);
			Tool = GetToolSprite(MenuBar::RECT);
			this->addChild(Tool);
			CurrentTool = MenuBar::RECT;
			break;
		case MenuBar::PEN:
			this->removeChild(Tool);
			Tool = GetToolSprite(MenuBar::PEN);
			this->addChild(Tool);
			CurrentTool = MenuBar::PEN;
			break;
		case MenuBar::INIT:
		default:
			break;
		}
	}
}

Sprite* Printer::GetToolSprite(MenuBar::PrintTool tool)
{
	switch (tool)
	{
	case MenuBar::LINE:
		return gcnew PrinterLine;
		break;
	case MenuBar::RECT:
		return gcnew PrinterRect;
		break;
	case MenuBar::PEN:
		return gcnew PrinterPen;
		break;
	case MenuBar::INIT:
	default:
		return gcnew Sprite;
		break;
	}
}

LinePara GetLinePara(Point p1, Point p2)
{
	LinePara LP;

	double m = 0;

	// �������  
	m = p2.x - p1.x;

	if (0 == m)
	{
		LP.k = 10000.0;
		LP.b = p1.y - LP.k * p1.x;
	}
	else
	{
		LP.k = (p2.y - p1.y) / (p2.x - p1.x);
		LP.b = p1.y - LP.k * p1.x;
	}

	return LP;
}

Point GetInLinePoint(float y, LinePara LP)
{
	return Point((y - LP.b) / LP.k, y);
}
