#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include "CursorFunctions.h"
#include "PrintShipFunctions.h"
#include "Color.h"
using namespace std;

// Dont forget to skip

void PrintLoadingBarFrame()
{
    TextColor(RED);
    CursorCoordinates(17, 20);
    int row = 3;
    int col = 52;
    for (int x = 0; x < row; x++)
    {
        wprintf(L"\n        ");
        for (int y = 0; y < col; y++)
        {
            // Drawing Corners
            if (x == 0 && y == 0) // ╔
            {
                wprintf(L"\x2554");
                wprintf(L"\x2550");
            }
            if (x == 2 && y == 0) // ╚
            {
                wprintf(L"\x255A");
                wprintf(L"\x2550");
            }
            if (x == 0 && y == col - 1) // ╗
            {
                wprintf(L"\x2550");
                wprintf(L"\x2557");
            }
            if (x == 2 && y == col - 1) // ╝ 
            {
                wprintf(L"\x2550");
                wprintf(L"\x255D");
            }

            // Drawing sides
            if (x == 0 && y != 0 && y != col - 1) //  ══
            {
                wprintf(L"\x2550");
                wprintf(L"\x2550");
            }
            else if (x == 2 && y != 0 && y != col - 1) // ══
            {
                wprintf(L"\x2550");
                wprintf(L"\x2550");
            }
            else if (x == 1 && y == 0) // ║ left
            {
                wprintf(L"\x2551");
                wprintf(L" ");
            }
            else if (x == 1 && y == col - 1) // ║ right
            {
                wprintf(L" ");
                wprintf(L"\x2551");
            }
            else if (x == 1 && y != 0 && y != col - 1) // Space in the inside of the rectangle
            {
                wprintf(L"  ");
            }
        }
    }
}

void StartLoading(int loaded_percentage, int max_percentage)
{
    for (int y = 1; y < loaded_percentage; y++)
    {
        CursorCoordinates(9 + y, 22);
        wprintf(L"\x2593");
    }

    int counter_for_periods = 0;
    for (int x = loaded_percentage; x < max_percentage; x++)
    {
        // Bar
        CursorCoordinates(9 + x, 22);
        wprintf(L"\x2593");

        // Loading 
        CursorCoordinates(56, 20);
        wprintf(L"Loading");

        // To show percentage of loading

        if (x < 100)
        {
            CursorCoordinates(61, 24);
            wprintf(L"%%");
        }
        else
        {
            CursorCoordinates(62, 24);
            wprintf(L"%%");
        }

        CursorCoordinates(58, 24);
        wprintf(L"%d ", x);

        // Periods for after the word "Loading"

        if (x % 5 == 0)
            counter_for_periods++;

        CursorCoordinates(63, 20);
        if (counter_for_periods % 4 == 1)
        {
            wprintf(L" .    ");
        }
        if (counter_for_periods % 4 == 2)
        {
            wprintf(L" . .  ");
        }
        if (counter_for_periods % 4 == 3)
        {
            wprintf(L" . . .");
        }
        if (counter_for_periods % 4 == 0)
        {
            wprintf(L"      ");
        }

        // Delay
        Sleep(50);

    }
}

void ShowLoadingScreen()
{
    system("cls");
    int result = _setmode(_fileno(stdout), _O_U16TEXT);;

    for (int x = 0; x < 101; x++)
    {
        CursorCoordinates(10, 1);
        if (x == 0)
        {
            system("cls");
            PrintShip1();
            PrintLoadingBarFrame();
            StartLoading(1, 21);
        }
        else if (x == 20)
        {
            system("cls");
            PrintShip2();
            PrintLoadingBarFrame();
            StartLoading(21, 41);
        }
        else if (x == 40)
        {
            system("cls");
            PrintShip3();
            PrintLoadingBarFrame();
            StartLoading(41, 61);
        }
        else if (x == 60)
        {
            if (x % 2 == 0)
            {
                TextColor(RED);
            }
            else
            {
                TextColor(PURPLE);
            }
            system("cls");
            PrintShip4();
            PrintLoadingBarFrame();
            StartLoading(61, 81);
        }
        else if (x == 80)
        {
            system("cls");
            PrintShip5();
            PrintLoadingBarFrame();
            StartLoading(81, 101);
        }
    }
    system("cls");
}
