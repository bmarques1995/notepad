#include "controller.hpp"

//..\..\Windows\Debug\bin\lrelease .\Notepad_en_US.xml -qm .\Notepad_en_US.bin



int main(int argc, char *argv[])
{
    {
        Controller controller(argc, argv);
        controller.run();
    }
    return 0;
}
