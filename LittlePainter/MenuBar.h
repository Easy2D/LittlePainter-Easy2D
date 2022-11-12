#pragma once
#include <easy2d/easy2d.h>
using namespace easy2d;

#include "PrinterPen.h"
#include "PrinterLine.h"
#include "PrinterRect.h"

class MenuBar
{
public:
    enum PrintTool
    {
        LINE,
        RECT,
        PEN,
        INIT
    };
public:
    static void init(Node* scene);

    static Color GetStrokeCurrentColor();
    static Color GetFillCurrentColor();
    static Color GetBGCurrentColor();

    static void SetStrokeCurrentColor(Color color);
    static void SetFillCurrentColor(Color color);
    static void SetBGCurrentColor(Color color);
    static void SetToolCurrentColor(PrintTool tool);

    static Image* GetPrintToolImage(PrintTool tool);
    static String GetPrintToolFilePath(PrintTool tool);
    static MenuBar::PrintTool GetCurrentPrintTool();

    static float GetMenuBarBottom();


private:
    static Color StrokeCurrentColor;                                               //��ǰ������ɫ
    static Color FillCurrentColor;                                                 //��ǰ�����ɫ
    static Color BGCurrentColor;                                                   //��ǰ������ɫ

    static ShapeNode* StrokeCurrentColorShape;                                     //��ǰ������ɫ
    static ShapeNode* FillCurrentColorShape;                                       //��ǰ�����ɫ
    static ShapeNode* BGCurrentColorShape;                                         //��ǰ������ɫ

    static MenuBar::PrintTool CurrentPrintTool;                                    //��ǰʹ�ù���
    static Sprite* CurrentTool;                                                    //��ǰʹ�ù���

    static Button* StrokeColorButton[40];                                          //������ɫ
    static Button* FillColorButton[40];                                            //�����ɫ
    static Button* BGColorButton[40];                                              //������ɫ

    static Button* PrintTools[4];                                                  //ֱ�ߣ����Σ�����

    static float MenuBarBottom;                                                    //ѡ��˵��ײ�����
};

