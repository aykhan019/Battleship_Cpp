#pragma once
#include <iostream>
#include<windows.h>
#include<conio.h>
#include <io.h>
#include <fcntl.h>
#include "CursorFunctions.h"
#include "PrintShipFunctions.h"
#include "Loading.h"
#include "StartGame.h"
using namespace std;

void ShowHowToPlay()
{
    TextColor(BLUE);
    wprintf(L"\n \x2588 Start / Preparation");
    TextColor(GREEN);
    wprintf(L"\n Each game can vary in the number of ships employed but a common practice is to have 5 ships of differing size (2 to 5)  squares. A destroyer is 4 squares long, a submarine is three squares long, a battleship is two squares longand carrier  is 1 square long.You place your ships on a grid of ten columns by ten rows. These represent the location of the ships   on a battlefield. Computer will also be in possession of a second grid of the same size.");
    TextColor(BLUE);
    wprintf(L"\n\n \x2588 In Play");
    TextColor(GREEN);
    wprintf(L"\n You will pick a square at random, writing it by its reference of column reference, row number (C3 for example). This    represents your firing a missile directly at that square. If the computer has any part of one of its ships positioned   on this square, it will be seem like \"X\". In this instance you will now be allowed to make another guess. This          continues until the attacking player misses. If you miss, this square will be seem like \"M\".");
    TextColor(BLUE);
    wprintf(L"\n\n \x2588 Victory");
    TextColor(GREEN);
    wprintf(L"\n The side who successfully destroys opponent’s all ships by hitting each square the other side occupy is the winner.");
    TextColor(BLUE);
    wprintf(L"\n\n \x2588 Game Symbols\n");
    TextColor(RED);
    wprintf(L"\n  X - Destroyed Ship\n");
    TextColor(PURPLE);
    wprintf(L"  M - Missed Shot\n");
    TextColor(CYAN);
    wprintf(L"  M - Last Missed Shot\n");
    TextColor(GREEN);
    wprintf(L" \x2590");
    wprintf(L"\x2588");
    wprintf(L"\x258C");
    wprintf(L" - Warship\n");

    wprintf(L"\n\n ");
    system("pause");
}

void ShowMenu();

void ShowChoices()
{
    TextColor(BLACK, WHITE);
    int Set[] = { GREY,GREY,GREY };
    int counter = 1;
    bool first_entry = true;
    char key;
    int result = _setmode(_fileno(stdout), _O_U16TEXT);

    HideCursor();
    while (true)
    {
        if (first_entry)
        {
            Set[0] = GREEN;
            first_entry = false;
        }

        PrintBATTLESHIP();
        CursorCoordinates(0, 17);
        PrintShips();

        CursorCoordinates(55, 12);
        TextColor(Set[0]);
        wprintf(L"PLAY GAME");

        CursorCoordinates(54, 13);
        TextColor(Set[1]);
        wprintf(L"HOW TO PLAY");

        CursorCoordinates(57, 14);
        TextColor(Set[2]);
        wprintf(L"EXIT");

        key = _getch();

        if (key == 72 && (counter > 1))
        {
            counter--;
        }
        if (key == 80 && (counter < 3))
        {
            counter++;
        }
        if (key == '\r')
        {
            if (counter == 1)
            {
                // Loading
                ShowLoadingScreen();
                Sleep(50); 
                // GAME
                //system("cls");
                StartGame();
                //system("cls");

            }
            if (counter == 2)
            {
                system("cls");
                // HOW TO PLAY
                ShowHowToPlay();
            }
            if (counter == 3)
            {
                // EXIT
                system("cls");
                system("exit");
                break;
            }
        }

        Set[0] = GREY;
        Set[1] = GREY;
        Set[2] = GREY;

        if (counter == 1)
        {
            Set[0] = GREEN;
        }
        if (counter == 2)
        {
            Set[1] = GREEN;
        }
        if (counter == 3)
        {
            Set[2] = GREEN;
        }
    }
}

void ShowMenu()
{
    ShowChoices();

}