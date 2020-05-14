#ifdef _WIN32
#include <windows.h>

// brings the cursor to the top left position allowing the overwriting of existing test
// does not actually clear the screen for efficiency reasons
void clear_screen()
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
}

#else
#include <iostream>
void clear_screen()
{
    std::cout << "\033c";
}

#endif