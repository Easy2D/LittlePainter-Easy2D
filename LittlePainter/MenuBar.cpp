#include "MenuBar.h"

Color colors[40] = {
        0x000000,
        0x0000FF,
        0x8A2BE2,
        0xA52A2A,
        0xD2691E,
        0x00008B,
        0xA9A9A9,
        0x006400,
        0xFF8C00,
        0x8B0000,
        0x9400D3,
        0x228B22,
        0xFFD700,
        0x808080,
        0x008000,
        0xADFF2F,
        0xADD8E6,
        0xE0FFFF,
        0x90EE90,
        0xD3D3D3,
        0xFFB6C1,
        0x20B2AA,
        0x87CEFA,
        0xFFFFE0,
        0xFFA500,
        0xFF4500,
        0xFFC0CB,
        0x800080,
        0xFF0000,
        0xC0C0C0,
        0x87CEEB,
        0xFFFAFA,
        0xEE82EE,
        0xF5DEB3,
        0xFFFFFF,
        0xF5F5F5,
        0xDEB887,
        0xFFFF00,
        0x9ACD32,
        Color::Transparent
};

#define BlockWidth 20

Color MenuBar::StrokeCurrentColor               =   Color::Black;                                                   //当前线条颜色
Color MenuBar::FillCurrentColor                 =   Color::Red;                                                     //当前填充颜色
Color MenuBar::BGCurrentColor                   =   Color::White;                                                   //当前背景颜色

ShapeNode* MenuBar::StrokeCurrentColorShape;                                                                        //当前线条颜色
ShapeNode* MenuBar::FillCurrentColorShape;                                                                          //当前填充颜色
ShapeNode* MenuBar::BGCurrentColorShape;                                                                            //当前背景颜色

MenuBar::PrintTool MenuBar::CurrentPrintTool    =   MenuBar::PrintTool(3);                                          //当前使用工具
Sprite* MenuBar::CurrentTool;                                                                                       //当前使用工具

Button* MenuBar::StrokeColorButton[40];                                                                             //线条颜色
Button* MenuBar::FillColorButton[40];                                                                               //填充颜色
Button* MenuBar::BGColorButton[40];                                                                                 //背景颜色

Button* MenuBar::PrintTools[4];                                                                                     //直线，矩形，蜡笔

float MenuBar::MenuBarBottom                    =   110;                                                            //选项菜单底部坐标

void MenuBar::init(Node * scene)
{
    //清空场景节点
    scene->removeAllChildren();

    //设置背景颜色
    Renderer::setBackgroundColor(BGCurrentColor);

    StrokeCurrentColor = Color::Black;
    FillCurrentColor = Color::Red;
    BGCurrentColor = Color::White;
    Renderer::setBackgroundColor(BGCurrentColor);
    CurrentPrintTool = MenuBar::PEN;
    CurrentTool = gcnew Sprite;

    //添加工具栏
    auto bar_shape = Shape::createRect(Rect(Point(0, 0), Size(Window::getWidth(), MenuBarBottom)));
    auto bar = gcnew ShapeNode(bar_shape);
    bar->setFillColor(Color(36,36,36, 0.5));
    scene->addChild(bar);
    
    //添加文字
    auto FillColorText = gcnew Text("填充颜色：");
    FillColorText->setFillColor(Color::Black);
    FillColorText->setScale(75 / FillColorText->getWidth());

    auto CurrentFillColor = Shape::createRect(Rect(Point(0, 0), Size(BlockWidth, BlockWidth)));
    FillCurrentColorShape = gcnew ShapeNode(CurrentFillColor);
    FillCurrentColorShape->setFillColor(FillCurrentColor);
    FillCurrentColorShape->setStrokeColor(Color::Gray);
    FillCurrentColorShape->setStrokeWidth(3);
    FillCurrentColorShape->setPos(20, 30);

    scene->addChild(FillCurrentColorShape);
    scene->addChild(FillColorText);



    auto StrokeColorText = gcnew Text("线条颜色：");
    StrokeColorText->setFillColor(Color::Black);
    StrokeColorText->setScale(75 / StrokeColorText->getWidth());
    StrokeColorText->setPosX(350);

    auto CurrentStrokeColor = Shape::createRect(Rect(Point(0, 0), Size(BlockWidth, BlockWidth)));
    StrokeCurrentColorShape = gcnew ShapeNode(CurrentStrokeColor);
    StrokeCurrentColorShape->setFillColor(StrokeCurrentColor);
    StrokeCurrentColorShape->setStrokeColor(Color::Gray);
    StrokeCurrentColorShape->setStrokeWidth(3);
    StrokeCurrentColorShape->setPos(350, 30);

    scene->addChild(StrokeColorText);
    scene->addChild(StrokeCurrentColorShape);



    auto BGColorText = gcnew Text("背景颜色：");
    BGColorText->setFillColor(Color::Black);
    BGColorText->setScale(75 / BGColorText->getWidth());
    BGColorText->setPosX(700);

    auto CurrentBGColor = Shape::createRect(Rect(Point(0, 0), Size(BlockWidth, BlockWidth)));
    BGCurrentColorShape = gcnew ShapeNode(CurrentBGColor);
    BGCurrentColorShape->setFillColor(BGCurrentColor);
    BGCurrentColorShape->setStrokeColor(Color::Gray);
    BGCurrentColorShape->setStrokeWidth(3);
    BGCurrentColorShape->setPos(700, 30);

    scene->addChild(BGColorText);
    scene->addChild(BGCurrentColorShape);



    auto ToolColorText = gcnew Text("工具：");
    ToolColorText->setFillColor(Color::Black);
    ToolColorText->setScale(20 / ToolColorText->getHeight());
    ToolColorText->setPosX(1050);

    CurrentTool->open(GetPrintToolFilePath(CurrentPrintTool));
    CurrentTool->setSize(35, 35);
    CurrentTool->setPosX(1100);

    scene->addChild(CurrentTool);
    scene->addChild(ToolColorText);

    for (int i = 0; i < 4; i++)
    {
        auto ToolImage = gcnew Sprite(GetPrintToolFilePath(MenuBar::PrintTool(i)));
        ToolImage->setSize(35, 35);
        PrintTools[i] = gcnew Button;
        PrintTools[i]->setNormal(ToolImage);
        PrintTools[i]->setPos(1050 + i * 37.5, 40);
        auto ClickToolButton = [i]()
        {
            MenuBar::SetToolCurrentColor(PrintTool(i));
        };
        PrintTools[i]->setClickFunc(ClickToolButton);

        scene->addChild(PrintTools[i]);
    }

    //int i = 0;
    /*
    * 行数 = i / 11 + 1
    * x 80
    */
    //Color::Value c = Color::Black; c <= Color::YellowGreen; c = Color::Value(c+1)
    for (int i = 0; i < 40; i++)
    {
        auto FillColor = Shape::createRect(Rect(Point(0, 0), Size(BlockWidth, BlockWidth)));
        auto FillColorShape = gcnew ShapeNode(FillColor);
        FillColorShape->setFillColor(colors[i]);
        FillColorShape->setStrokeColor(Color::Gray);
        FillColorShape->setStrokeWidth(3);
        int row = i / 10;
        int col = 0;
        if (i < 10)
        {
            col = i;
        }
        else
        {
            col = i - 10 * row;
        }

        FillColorButton[i] = gcnew Button;
        FillColorButton[i]->setNormal(FillColorShape);
        FillColorButton[i]->setPos(80 + col * 25, 5 + row * 25);
        FillColorButton[i]->setSize(BlockWidth, BlockWidth);
        auto ClickFillColorFunc = []()
        {
            int row = (Input::getMouseX() - 80) / 25;
            int col = (Input::getMouseY() - 5) / 25;
            MenuBar::SetFillCurrentColor(colors[col * 10 + row]);
        };
        FillColorButton[i]->setClickFunc(ClickFillColorFunc);
        scene->addChild(FillColorButton[i]);



        auto StrokeColor = Shape::createRect(Rect(Point(0, 0), Size(BlockWidth, BlockWidth)));
        auto StrokeColorShape = gcnew ShapeNode(StrokeColor);
        StrokeColorShape->setFillColor(colors[i]);
        StrokeColorShape->setStrokeColor(Color::Gray);
        StrokeColorShape->setStrokeWidth(3);

        StrokeColorButton[i] = gcnew Button;
        StrokeColorButton[i]->setNormal(StrokeColorShape);
        StrokeColorButton[i]->setPos(430 + col * 25, 5 + row * 25);
        StrokeColorButton[i]->setSize(BlockWidth, BlockWidth);
        auto ClickStrokeColorFunc = []()
        {
            int row = (Input::getMouseX() - 430) / 25;
            int col = (Input::getMouseY() - 5) / 25;
            MenuBar::SetStrokeCurrentColor(colors[col * 10 + row]);
        };
        StrokeColorButton[i]->setClickFunc(ClickStrokeColorFunc);
        scene->addChild(StrokeColorButton[i]);



        auto BGColor = Shape::createRect(Rect(Point(0, 0), Size(BlockWidth, BlockWidth)));
        auto BGColorShape = gcnew ShapeNode(BGColor);
        BGColorShape->setFillColor(colors[i]);
        BGColorShape->setStrokeColor(Color::Gray);
        BGColorShape->setStrokeWidth(3);

        BGColorButton[i] = gcnew Button;
        BGColorButton[i]->setNormal(BGColorShape);
        BGColorButton[i]->setPos(780 + col * 25, 5 + row * 25);
        BGColorButton[i]->setSize(BlockWidth, BlockWidth);
        auto ClickBGColorFunc = []()
        {
            int row = (Input::getMouseX() - 780) / 25;
            int col = (Input::getMouseY() - 5) / 25;
            MenuBar::SetBGCurrentColor(colors[col * 10 + row]);
        };
        BGColorButton[i]->setClickFunc(ClickBGColorFunc);
        scene->addChild(BGColorButton[i]);

        //i++;
    }
}

Color MenuBar::GetStrokeCurrentColor()
{
    return StrokeCurrentColor;
}

Color MenuBar::GetFillCurrentColor()
{
    return FillCurrentColor;
}

Color MenuBar::GetBGCurrentColor()
{
    return BGCurrentColor;
}

void MenuBar::SetStrokeCurrentColor(Color color)
{
    StrokeCurrentColor = color;
    StrokeCurrentColorShape->setFillColor(color);
}

void MenuBar::SetFillCurrentColor(Color color)
{
    FillCurrentColor = color;
    FillCurrentColorShape->setFillColor(color);
}

void MenuBar::SetBGCurrentColor(Color color)
{
    BGCurrentColor = color;
    BGCurrentColorShape->setFillColor(color);
    Renderer::setBackgroundColor(color);
}

void MenuBar::SetToolCurrentColor(PrintTool tool)
{
    CurrentPrintTool = tool;
    CurrentTool->open(GetPrintToolFilePath(tool));
    CurrentTool->setSize(35, 35);
}

Image* MenuBar::GetPrintToolImage(PrintTool tool)
{
    auto image = Image::load("");
    switch (tool)
    {
    case MenuBar::LINE:
        image = Image::load("./Tools/line.png");
        break;
    case MenuBar::RECT:
        image = Image::load("./Tools/rect.png");
        break;
    case MenuBar::PEN:
        image = Image::load("./Tools/pen.png");
        break;
    case MenuBar::INIT:
        image = Image::load("./Tools/init.png");
        break;
    default:
        break;
    }
    return image;
}

String MenuBar::GetPrintToolFilePath(PrintTool tool)
{
    switch (tool)
    {
    case MenuBar::LINE:
        return "./Tools/line.png";
        break;
    case MenuBar::RECT:
        return"./Tools/rect.png";
        break;
    case MenuBar::PEN:
        return"./Tools/pen.png";
        break;
    case MenuBar::INIT:
        return"./Tools/init.png";
        break;
    default:
        return "";
        break;
    }
}

MenuBar::PrintTool MenuBar::GetCurrentPrintTool()
{
    return CurrentPrintTool;
}

float MenuBar::GetMenuBarBottom()
{
    return MenuBarBottom;
}
