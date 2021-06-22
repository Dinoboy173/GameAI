#include "Application.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

int main(int argc, char** argv)
{
    {
        Application app(800, 450, "GameAI");
        app.Run();
    }

    return 0;
}