#include "./Menu/Application.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"
#include <iostream>
#include <random>
#include <time.h>
#include <Graph.h>

int main(int argc, char** argv)
{
    //TestGraph();
    //return 0;

    srand(time(NULL));

    {
        Application app(1024, 1024,  "GameAI");
        app.Run();
    }

    return 0;
}