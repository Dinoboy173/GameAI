#include "Application.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"

int main(int argc, char** argv)
{
    {
        Application app(1080, 1920, "Forest Sim");
        app.Run();
    }

    return 0;
}