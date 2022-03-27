#pragma once
#include <iostream>
#include <Windows.h>

enum colors {
    BLACK = 0, RED = 4, GREEN = 2, YELLOW = 14, BLUE = 1, PURPLE = 5, CYAN = 3, GREY = 8, WHITE = 7
};

void TextColor(int fg, int bg = WHITE) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, fg | (bg << 4));
}