#ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#include "App/Application/Application.h"

extern Application* APPLICATION = new Application();

int main(int argc, char** argv)
{    
    APPLICATION->Start();

    return 0;
}
