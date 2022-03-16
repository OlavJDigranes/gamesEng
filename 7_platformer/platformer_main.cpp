#include "engine.h"
#include "game.h"
#include "scenes/scene_menu.h"

using namespace std;

MenuScene menu;
Level1Scene level1;
Level2Scene level2;
Level3Scene level3;

int main() {
    //TODO: Visual Studio error at "future", Compile time, Breakpoint on line below shows it. 

    /*
    Exception thrown at 0x00007FFAC17E4F69 in 7_PLATFORMER.exe: Microsoft C++ exception: std::basic_string<char,std::char_traits<char>,std::allocator<char> > at memory location 0x000000C42F5FEEA0.
    Exception thrown at 0x00007FFAC17E4F69 in 7_PLATFORMER.exe: Microsoft C++ exception: std::basic_string<char,std::char_traits<char>,std::allocator<char> > at memory location 0x000000C42F4FF090.
    Unhandled exception at 0x00007FFAC17E4F69 in 7_PLATFORMER.exe: Microsoft C++ exception: std::basic_string<char,std::char_traits<char>,std::allocator<char> > at memory location 0x000000C42F4FF090.

    Could it be something about C++ std chnages, needing to inlcude something?
    */

    Engine::Start(1280, 720, "Platformer",&menu);
}