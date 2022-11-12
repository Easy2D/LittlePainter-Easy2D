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
    static Color StrokeCurrentColor;                                               //当前线条颜色
    static Color FillCurrentColor;                                                 //当前填充颜色
    static Color BGCurrentColor;                                                   //当前背景颜色

    static ShapeNode* StrokeCurrentColorShape;                                     //当前线条颜色
    static ShapeNode* FillCurrentColorShape;                                       //当前填充颜色
    static ShapeNode* BGCurrentColorShape;                                         //当前背景颜色

    static MenuBar::PrintTool CurrentPrintTool;                                    //当前使用工具
    static Sprite* CurrentTool;                                                    //当前使用工具

    static Button* StrokeColorButton[40];                                          //线条颜色
    static Button* FillColorButton[40];                                            //填充颜色
    static Button* BGColorButton[40];                                              //背景颜色

    static Button* PrintTools[4];                                                  //直线，矩形，蜡笔

    static float MenuBarBottom;                                                    //选项菜单底部坐标
};

